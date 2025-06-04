#include <algorithm>
#include <cmath>
#include <deque>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

#include "windows.hpp"

struct iir_filter
{
    std::vector<double> a;
    std::vector<double> b;

    std::deque<double> last_values;
    std::deque<double> last_filtered_values;

    void set_order(int order)
    {
        a.resize(order);
        b.resize(order);
        last_values.resize(order);
        last_filtered_values.resize(order);
    }

    void reset()
    {
        std::fill(last_values.begin(),last_values.end(),0);
        std::fill(last_filtered_values.begin(),last_filtered_values.end(),0);
    }

    double process(double v)
    {
        last_values.push_back(v);
        last_values.pop_front();
        double fv = std::inner_product(last_values.rbegin(),last_values.rend(),b.begin(),0.0) 
        - std::inner_product(last_filtered_values.rbegin(),last_filtered_values.rend() - 1,a.begin() + 1,0.0);
        last_filtered_values.push_back(fv);
        last_filtered_values.pop_front();
        return fv;
    }

    template <typename InputIt, typename OutputIt>
    void process (InputIt begin, InputIt end, OutputIt output)
    {
        // auto s = std::distance(begin,end);

        // for (auto i = 0; i < s; ++i)
        // {
        //     *(output + i) = process(*(begin + i));
        // }

        for (auto it = begin; it != end; ++it, ++output)
        {
            *output = process(*it);
        }
    }

    template <typename ContainerIn,typename ContainerOut = ContainerIn>
    ContainerOut process(ContainerIn a) 
    {
        ContainerOut o(std::size(a));
        process(std::begin(a),std::end(a),std::begin(o));
        return o;
    }

    double operator() (double v)
    {
        return process(v);
    }

    template <typename InputIt, typename OutputIt>
    void operator() (InputIt begin, InputIt end, OutputIt target)
    {
        process(begin,end,target);
    }

    template <typename ContainerIn,typename ContainerOut = ContainerIn>
    ContainerOut operator() (ContainerIn a)
    {
        return process(a);
    }

    
};

struct cascade_filter
{
    std::vector<iir_filter> filters;

    template<typename InputIt, typename OutputIt>
    void process(InputIt begin, InputIt end, OutputIt target)
    {
        auto s = std::distance(begin,end);
        std::vector<decltype(*begin)> intermediate_values(begin,end);
        std::vector<decltype(*begin)> intermediate_values_2(s);

        for (auto i  = 0; i < filters.size()-1; ++i)
        {
            intermediate_values_2 = filters[i].process(intermediate_values);
            std::swap(intermediate_values,intermediate_values_2);
        }   
        filters.back().process(intermediate_values.begin(),intermediate_values.end(),target);
    }

    template <typename ContainerIn, typename ContainerOut = ContainerIn>
    ContainerOut process(ContainerIn a)
    {
        ContainerOut o(std::size(a));
        process(std::begin(a),std::end(a),std::begin(o));
        return o;
    }
};

auto design_butterworth_low_pass_filter(double cutoff_freq,double sample_rate, bool soft_freq = true)
{
    if (soft_freq) cutoff_freq = std::clamp(cutoff_freq, 0.01*sample_rate,0.49*sample_rate);

    double omega = 2.0 * M_PI * cutoff_freq / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    // double alpha = sin_omega / (2.0 * sqrt(2.0));
    double alpha = sin_omega / (sqrt(2.0));

    double a0 = 1.0 + alpha;
    double b0 = (1.0 - cos_omega) / 2.0 / a0;
    double b1 = (1.0 - cos_omega) / a0;
    double b2 = b0;
    double a1 = -2.0 * cos_omega / a0;
    double a2 = (1.0 - alpha) / a0;

    iir_filter f;

    f.a = {1.0, a1, a2};
    f.b = {b0, b1, b2};
    f.last_filtered_values = {0,0,0};
    f.last_values = {0,0,0};

    return f;
}

auto design_butterworth_high_pass_filter(double cutoff_freq,double sample_rate, bool soft_freq = true)
{
    if (soft_freq) cutoff_freq = std::clamp(cutoff_freq, 0.01*sample_rate,0.49*sample_rate);

    double omega = 2.0 * M_PI * cutoff_freq / sample_rate;
    double sin_omega = sin(omega);
    double cos_omega = cos(omega);
    // double alpha = sin_omega / (2.0 * sqrt(2.0));
    double alpha = sin_omega / (sqrt(2.0));

    double a0 = 1.0 + alpha;

    //               | There is the difference
    //               v
    double b0 = (1.0 + cos_omega) / 2.0 / a0;
    double b1 = -(1.0 + cos_omega) / a0;
    double b2 = b0;
    double a1 = -2.0 * cos_omega / a0;
    double a2 = (1.0 - alpha) / a0;


    iir_filter f;

    f.a = {1.0, a1, a2};
    f.b = {b0, b1, b2};
    f.last_filtered_values = {0,0,0};
    f.last_values = {0,0,0};

    return f;
}



struct fir_filter
{
    std::vector<double> impulse;
    std::deque<double> last_values;

    fir_filter(std::vector<double> impulse) :impulse(impulse), last_values(impulse.size(), 0.0){
        normalize();
    }

    void set_size(int size)
    {
        last_values.resize(size);
        impulse.resize(size);
    }

    void normalize()
    {
        double impulse_sum = std::accumulate(impulse.begin(),impulse.end(),0.0);
        std::for_each(impulse.begin(),impulse.end(),[&](auto& v){ v /= impulse_sum;});
    }

    void reset()
    {
        std::fill(last_values.begin(),last_values.end(),0.0);
    }

    double process(double v)
    {
        last_values.push_back(v);
        last_values.pop_front();
        double fv = std::inner_product(last_values.begin(),last_values.end(),impulse.rbegin(),0.0);
        return fv;
    }

    template <typename InputIt, typename OutputIt>
    void process(InputIt begin, InputIt end, OutputIt output)
    {
        auto s = std::distance(begin,end);

        for (auto i = 0; i < s; ++i)
        {
            *(output + i) = process(*(begin+i));
        }
    }

    template <typename ContainerIn, typename ContainerOut = ContainerIn>
    ContainerOut process(ContainerIn a)
    {
        ContainerOut c(std::size(a));
        process(std::begin(a),std::end(a),std::begin(c));
        return c;
    }

    double operator() (double v)
    {
        return process(v);
    }

    template <typename InputIt, typename OutputIt>
    void operator() (InputIt begin, InputIt end, OutputIt target)
    {
        process(begin,end,target);
    }

    template <typename ContainerIn,typename ContainerOut = ContainerIn>
    ContainerOut operator() (ContainerIn a)
    {
        return process(a);
    }
};

inline double sinc(double x)
{
    if (std::abs(x) < std::numeric_limits<double>::epsilon()) return 1.0;
    else return sin(M_PI * x) / M_PI / x;
}

template <typename OutputIt>
void generate_lowpass_sinc_filter(OutputIt begin, OutputIt end, double cutoff_freq, double sample_rate, bool soft_freq = true)
{
    if (soft_freq) cutoff_freq = std::clamp(cutoff_freq, 0.01*sample_rate,0.49*sample_rate);
    // else cutoff_freq = std::clamp(cutoff_freq, 0.01*sample_rate,0.49*sample_rate);

    auto s = std::distance(begin,end);

    int i = 0;
    auto v = signal_processing::windows::Hamming(s);

    for (auto it = begin; it != end; ++it)
    {
        auto& f = cutoff_freq;
        *it = 2.0 * f / sample_rate * sinc(2.0 * f * (i - s/2) /sample_rate);
        *it *= v[i];
        ++i;
    }
};


template <typename OutputIt>
void generate_highpass_sinc_filter(OutputIt begin, OutputIt end, double cutoff_freq, double sample_rate, bool soft_freq = true)
{
    generate_lowpass_sinc_filter(begin,end,cutoff_freq,sample_rate,soft_freq);
    std::for_each(begin,end,[](auto& v){v = -v;});
    if (begin != end) *(begin + (end - begin) / 2) += 1;
}


template <typename Container = std::vector<double>>
Container generate_lowpass_sinc_filter(int size, double cutoff_freq, double sample_rate)
{
    Container c(size);
    generate_lowpass_sinc_filter(std::begin(c),std::end(c),cutoff_freq,sample_rate);
    return c;
}

template <typename Container = std::vector<double>>
Container generate_highpass_sinc_filter(int size, double cutoff_freq, double sample_rate)
{
    Container c(size);
    generate_highpass_sinc_filter(std::begin(c),std::end(c),cutoff_freq,sample_rate);
    return c;
}