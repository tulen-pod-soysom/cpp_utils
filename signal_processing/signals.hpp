#include "../math/sampling.hpp"
#include <algorithm>
#include <cmath>
#include <random>

namespace signals
{
    template <typename Container = std::vector<double>>
    Container generate_sine(double sample_rate, int n, double a = 1, double f = 1, double phase = 0)
    {
        Container c(n);
        sampler s;
        s.set_sample_rate(sample_rate);
        s(std::begin(c),std::end(c),[&](auto x) {return a*sin(2*M_PI*f*x + phase);});
        return c;
    }

    template <typename Container = std::vector<double>>
    Container generate_meandr(double sample_rate, int n, double a = 1, double f = 1, double phase = 0)
    {
        Container c(n);
        sampler s;
        s.set_sample_rate(sample_rate);
        s(std::begin(c),std::end(c),[&](auto x) {return (fmod(2*M_PI*f*x + phase,2*M_PI) > M_PI)? a : -a;});
        return c;
    }


    template <typename Container = std::vector<double>>
    Container generate_saw(double sample_rate, int n, double a = 1, double f = 1, double phase = 0)
    {
        Container c(n);
        sampler s;
        s.set_sample_rate(sample_rate);
        s(std::begin(c),std::end(c),[&](auto x) {return fmod(f*x + phase/ 2.0/M_PI,1); });
        return c;
    }

    template <typename Container = std::vector<double>>
    Container generate_triangle(double sample_rate, int n, double a = 1, double f = 1, double phase = 0)
    {
        Container c(n);
        sampler s;
        s.set_sample_rate(sample_rate);
        s(std::begin(c),std::end(c),[&](auto x) {auto v = fmod(f*x + phase/ 2.0/M_PI + 1.0/4.0,1); return v > 0.5? a*(1 - 4*(v-0.5)) : 4*a*(v-0.25); });
        return c;
    }

    template <typename Container = std::vector<double>>
    Container generate_impulse(int n, int offset = 0, double a = 1)
    {
        Container c(n);
        *(std::begin(c) + offset) = a;
        return c;
    }
    


    template <typename Container = std::vector<double>>
    Container generate_white_noise(int n, double sigma = 1.0)
    {
        Container c(n);

        std::random_device rd;

        std::normal_distribution<double> dist(0,sigma);

        std::generate(std::begin(c),std::end(c),[&]{return dist(rd);});

        return c;
    }

}