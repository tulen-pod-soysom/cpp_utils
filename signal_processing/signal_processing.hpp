#ifndef SIGNAL_PROCESSING_UTILS
#define SIGNAL_PROCESSING_UTILS
#include <cmath>
#include <complex>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include "../math/fft.hpp"


namespace signal_processing
{

    template<typename InputIt>
    void spectral_characteristics_to_file(InputIt begin, InputIt end, std::string prefix = "signal")
    {
        std::ofstream s(prefix + ".txt");
        std::ofstream s_abs(prefix + "_abs.txt");
        std::ofstream s_ph(prefix + "_ph.txt");

        std::copy(begin,end,
            std::ostream_iterator<double>(s,"\n"));
        
        auto size = std::distance(begin,end);

        std::vector<std::complex<double>> v_f(size);

        fft(begin,end,v_f.begin(),-1.0);

        auto v_abs = abs(v_f);
        auto v_ph = atan2(v_f);
        
        std::copy(v_abs.begin(),v_abs.end(),
            std::ostream_iterator<double>(s_abs,"\n"));

        std::copy(v_ph.begin(),v_ph.end(),
            std::ostream_iterator<double>(s_ph,"\n"));

        s.close(); s_abs.close(); s_ph.close();

        // std::string command = "gnuplot -p -e \" set term qt size 1600,900; set autoscale noextend; set multiplot layout 2,2 columns; plot 'signal.txt' w l t 'сигнал'; \
        plot 'signal_abs.txt' w l t 'АЧХ сигнала'; plot 'signal_ph.txt' w l t 'ФЧХ сигнала'; plot 0; unset multiplot; pause mouse close;\"";
        // system(command.c_str());

    }

template <typename T>
T abs2(T a)
{
    return abs(a*a);
}

template <typename T>
T abs2(std::complex<T> a)
{
    return a.imag() * a.imag() + a.real() * a.real();
}

template <typename Matrix1, typename Matrix2>
auto MSE(Matrix1& m1, Matrix2& m2, unsigned rows, unsigned cols)
{
    double error = 0.0;
    for (auto i = 0; i < rows; ++i)
        for (auto j = 0; j < cols; ++j)
    {
        error += abs2(m1(i,j) - m2(i,j));
    }

    return error /(double)rows /(double)cols;
}

template <typename InputIt>
auto MSE(InputIt begin1, InputIt end1, InputIt begin2)
{
    double sum = 0;
    auto size = end1 - begin1;

    auto i = begin1;
    auto j = begin2;
    for (; i != end1; ++i, ++j)
    {
        sum += abs2(*i - *j);
    }
    return sum / (double) size;
}

template <typename Container>
auto MSE(Container a, Container b)
{
    return MSE(std::begin(a),std::end(a),std::begin(b));
}

template <typename T>
auto PSNR(double MSE, T peak = 255)
{
    return 10 * std::log10(peak*peak/MSE);
}


#ifdef ARMA_INCLUDES
template <typename T1, typename T2>
auto MSE(arma::Mat<T1>& m1, arma::Mat<T2>& m2)
{
    assert(m1.n_cols == m2.n_cols);
    assert(m1.n_rows == m2.n_rows);
    return MSE(m1,m2,m1.n_rows,m1.n_cols);
}
#endif


#endif // SIGNAL_PROCESSING_UTILS
}