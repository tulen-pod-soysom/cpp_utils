#pragma once
#include "cpp_utils/math/sampling.hpp"
#include <algorithm>
#include <cmath>
#include <random>
#include <type_traits>
#include <complex>

namespace sgnls
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
    


    template <typename Type = double, typename Container = std::vector<Type>>
    Container generate_awgn(int n, double sigma = 1.0)
    {
        Container c(n);

        std::random_device rd;
        std::mt19937 mt(rd());


        if constexpr (std::is_same_v<Type, std::complex<double>>)
        {
            std::normal_distribution<double> dist(0,sigma/sqrt(2));
            std::generate(std::begin(c),std::end(c),[&]{return std::complex<double>(dist(mt),dist(mt));});
        }
        else
        {
            std::normal_distribution<double> dist(0,sigma);
            std::generate(std::begin(c),std::end(c),[&]{return dist(mt);});
        }

        return c;
    }



    template <typename InputIt, typename Random>
    void generate_random_bits(Random& rd, InputIt begin, InputIt end, double zero_chance = 0.5, double one_chance = 0.5)
    {
        std::discrete_distribution<> dist({zero_chance,one_chance});

        for (auto it = begin; it != end; ++it)
        {
            *it = dist(rd);
        }
    }

    template <typename Container = std::vector<bool>, typename Random>
    Container generate_random_bits(Random &rd, int n, double zero_chance = 0.5, double one_chance = 0.5)
    {
        Container c(n);
        generate_random_bits(rd,std::begin(c),std::end(c),zero_chance,one_chance);
        return c;
    }


}
