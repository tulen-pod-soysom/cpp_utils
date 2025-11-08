#pragma once

#include "cpp_utils/math/constants.hpp"
#include <cmath>
#include <queue>
#include <type_traits>
#include <vector>
#include <complex>

namespace modulation 
{
    // struct AM
}

namespace manipulation
{
    using namespace std::complex_literals;

    template <typename Complex_type = std::complex<double>, typename Real_type = double>
    auto quadrature_to_real(Complex_type c, Real_type r, double frequency, double t)
    {
        double phase = constants::tau *frequency * t;
        return c.real() * std::cos(phase) - c.imag() * std::sin(phase);
    }



    template <typename Derived, typename OutputType = std::complex<double>>
    struct manipulator_base
    {
        manipulator_base(double sample_rate, double symbol_rate) :sample_rate(sample_rate), symbol_rate(symbol_rate), t(0) {}

        double sample_rate;
        double symbol_rate;
        double t;

        std::queue<bool> bits;

        int bits_per_symbol = 1;
        int current_symbol = 0;

        void push_bit(bool bit)
        {
            this->bits.push(bit);
        }
        template <typename Container = std::vector<bool>>
        void push_bits(Container bits)
        {
            for (auto i = 0; i < bits.size(); ++i)
            this->bits.push(bits[i]);
        }

        void take_symbol()
        {
            if (bits.size() >= bits_per_symbol)
            {
                current_symbol = 0;

                for (int i = 0; i < bits_per_symbol; ++i)
                {
                    bool bit = bits.front();
                    bits.pop();

                    current_symbol = (current_symbol << 1) | bit;
                }
            }
        }

        OutputType process()
        {
            t += 1.0/sample_rate;

            if (t >= 1.0/symbol_rate) 
            {
                t -= 1.0/symbol_rate;
                
                take_symbol(); 

                // if (!bits.empty())
                // {
                //     current_bit = bits.front();
                //     bits.pop();
                // } 
            }
            return static_cast<Derived*>(this)->process_impl();
        }

        template <typename Container=std::vector<OutputType>>
        Container process(int n)
        {
            Container c(n);
            for (auto i =0; i < n; ++i)
                c[i] = process();

            return c;
        }
        template <typename Container=std::vector<OutputType>>
        Container full_process()
        {
            // Container c(n);
            // for (auto i =0; i < n; ++i)
                // c[i] = process();
            Container c;
            while (bits.size() >= bits_per_symbol) {
                c.push_back(process());
            }

            return c;
        }       

        void reset()
        {
            bits = {};
            t = 0;
            current_symbol = 0;
            static_cast<Derived*>(this)->reset_impl();
        }
    };


    inline double phase_increment(double phase, double sample_rate, double frequency)
    {
        phase += constants::tau*frequency/sample_rate; 
        if (phase >= constants::tau) phase = fmod(phase,constants::tau);
        return phase;
    }


    template <typename OutputType = std::complex<double>>
    struct AM2 : manipulator_base<AM2<>,OutputType>
    {
        using manip_base = manipulator_base<AM2<OutputType>,OutputType>;

        using manip_base::sample_rate;
        using manip_base::bits;
        using manip_base::current_symbol;


        AM2(double sample_rate, double symbol_rate, double frequency = 1) :manip_base(sample_rate, symbol_rate), frequency(frequency) {}
        double level0 = 0;
        double level1 = 1;
        double frequency = 1;
        double phase = 0;

        OutputType process_impl()
        {
            if (bits.empty()) return 0.0;
            auto a = current_symbol? level1 : level0;
            phase = phase_increment(phase, sample_rate, frequency);
            // phase += constants::tau*frequency/sample_rate;
            // if (phase >= constants::tau) phase -= constants::tau;
            // if constexpr (std::is_same_v<OutputType, double>)
                // return a*std::cos(phase);
            // else if constexpr (std::is_same_v<OutputType,std::complex<double>()>)
                return a*std::polar(1.0,phase);

            // return {};
        }

        void reset_impl()
        {
            phase = 0;
        }
    };

    template <typename OutputType = std::complex<double>>
    struct PM2 : manipulator_base<PM2<>,OutputType>
    {
        using manip_base = manipulator_base<PM2<OutputType>,OutputType>;

        using manip_base::sample_rate;
        using manip_base::bits;
        using manip_base::current_symbol;

        PM2(double sample_rate, double symbol_rate, double frequency = 1) :manip_base(sample_rate, symbol_rate), frequency(frequency) {}
        double amplitude = 1;
        double frequency = 1;
        double phase = 0;

        OutputType process_impl()
        {
            if (bits.empty()) return 0.0;

            phase = phase_increment(phase, sample_rate, frequency);
            // phase += constants::tau*frequency/sample_rate;
            // if (phase >= constants::tau) phase -= constants::tau;

            return amplitude * (current_symbol? 1.0 : -1.0) * std::polar(1.0,phase);
            // return amplitude*std::sin(phase + (current_symbol? constants::pi : 0));
        }

        void reset_impl()
        {
            phase = 0;
        }
    };

    struct PM4 : manipulator_base<PM4>
    {
        using manip_base = manipulator_base<PM4>;

        using manip_base::sample_rate;
        using manip_base::bits;
        using manip_base::current_symbol;

        PM4(double sample_rate, double symbol_rate, double frequency = 1) :manip_base(sample_rate, symbol_rate), frequency(frequency) {
            bits_per_symbol = 2;
        }
        double amplitude = 1;
        double frequency = 1;
        double phase = 0;


        std::complex<double> process_impl()
        {
            if (bits.size() <= bits_per_symbol) return 0.0;
            phase = phase_increment(phase, sample_rate, frequency);
            // phase += constants::tau*frequency/sample_rate;
            // if (phase >= constants::tau) phase -= constants::tau;

            double I = amplitude / sqrt(2);
            double Q = amplitude / sqrt(2);

            // Gray code alignment
            switch (current_symbol) {
                case 0: I = -I; Q = -Q; break;
                case 1: I = -I; break;
                case 2: Q = -Q; break;
                case 3: break;
            }

            return std::complex{I,Q} * std::polar(1.0, phase);
        }        

        void reset_impl()
        {
            phase = 0;
        }
    };




    template <typename OutputType = std::complex<double>>
    struct MFM : manipulator_base<MFM<>,OutputType>
    {
        using manip_base = manipulator_base<MFM<OutputType>,OutputType>;

        using manip_base::symbol_rate;
        using manip_base::sample_rate;
        using manip_base::bits;
        using manip_base::current_symbol;

        MFM(double sample_rate, double symbol_rate, double frequency = 1) :manip_base(sample_rate, symbol_rate), frequency(frequency) {}
        double amplitude = 1;
        double frequency = 1;
        double phase = 0;

        OutputType process_impl()
        {
            if (bits.empty()) return 0.0;
            double freq = current_symbol? frequency-symbol_rate/2 : frequency+symbol_rate/2;
            phase = phase_increment(phase, sample_rate, frequency);
            // phase += constants::tau*freq/sample_rate;
            // if (phase >= constants::tau) phase -= constants::tau;
            return amplitude*std::polar(1.0, phase);
            // return amplitude*std::sin(phase);
        }

        void reset_impl()
        {
            phase = 0;
        }
    };
}
