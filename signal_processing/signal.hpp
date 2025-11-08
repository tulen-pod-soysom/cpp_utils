#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "cpp_utils/math/constants.hpp"
#include <cmath>

namespace signal_processing 
{
    struct signal_function
    {};

    struct sine_function : public signal_function
    {
        sine_function(double A, double f, double phase) : A(A), f(f), phase(phase){}
        double A{1},f{1},phase{0};

        void set_amplitude(double A) { this->A = A; }
        void set_frequency(double f) { this->f = f; }
        void set_period(double T) { this->f = 1.0 / T; }
        void set_phase(double phase) { this->phase = phase; }
        void set_shift(double shift) { this->phase = -constants::tau*f*shift;} // ??????????????

        double operator () (double x)
        {
            return A*sin(constants::tau*f*x + phase);
        }
    };

    struct meandr_function : public signal_function
    {
        meandr_function(double A = 1, double T = 1, double fill = 0.5, double shift = 0) :A(A),T(T),fill(fill),shift(shift){};
        double A{1},T{1},shift{0};
        double fill = 0.5;

        bool bipolar = true;

        void set_amplitude(double A) { this->A = A; }
        void set_frequency(double f) { this->T = 1.0/f; }
        void set_period(double T) { this->T = T; }
        void set_shift(double x) { this->shift = x; }
        void set_fill(double fill_part) {this->fill = fill_part;}
        void set_duty(double duty_factor) {this->fill = 1/duty_factor;}

        double operator () (double x)
        {
            double x_ = (x-shift)/T;
            double v;
            if (bipolar)
                v = (x_ - std::floor(x_) < fill)? 1:-1;
            else
                v = (x_ - std::floor(x_) < fill)? 1:0;
            return A*v;
        }
    };

    struct meandr_impulse_function : public signal_function
    {
        meandr_impulse_function(double A = 1, double T = 1, double shift = 0) :A(A),T(T),shift(shift){};
        double A{1},T{1},shift{0};
        double operator () (double x)
        {
            if ((x >= shift) && (x <= shift + T)) return 1;
            else return 0.0;
        }
    };

    struct saw_function : public signal_function
    {
        saw_function(double A = 1, double T = 1, double shift = 0) :A(A),T(T),shift(shift){};
        double A{1},T{1},shift{0};

        bool bipolar = true;

        void set_amplitude(double A) { this->A = A; }
        void set_frequency(double f) { this->T = 1.0/f; }
        void set_period(double T) { this->T = T; }
        void set_shift(double x) { this->shift = x; }

        double operator () (double x)
        {
            double x_ = (x-shift)/T;
            double v;
            if (bipolar)
                v = (x_ - std::floor(x_) - 0.5) * 2;
            else
                v = x_ - std::floor(x_);
            return A*v;
        }
    };

    struct triangle_function : public signal_function
    {
        triangle_function(double A = 1, double T = 1, double shift = 0) :A(A),T(T),shift(shift){};
        double A{1},T{1},shift{0};

        void set_amplitude(double A) { this->A = A; }
        void set_frequency(double f) { this->T = 1.0/f; }
        void set_period(double T) { this->T = T; }
        void set_shift(double x) { this->shift = x; }

        double operator () (double x)
        {
            double x_ = (x-shift)/T;
            x_ = x_ - std::floor(x_);

            double v;
            if ((x_ >= 0.25) && (x_ <= 0.75))
                v = 2 - 4*x_;
            else if (x_ < 0.25)
                v = 4 * x_;
            else
                v = 4 * x_ - 4;

            return v;
        }
    };

    struct exp_function : public signal_function
    {
        exp_function(double A = 1, double B = 1, double shift = 0) :A(A),B(B),shift(shift){};
        double A{1},B{-1},shift{0};

        void set_amplitude(double A) { this->A = A; }
        void set_exponent(double alpha) {this->B = alpha;}
        void set_time_constant(double theta) {B = -1.0/theta;}
        void set_shift(double x) { this->shift = x; }

        double operator () (double x)
        {
            return A*exp(B*(x - shift));
        }
    };

    struct exp_impulse_function : public exp_function
    {
        using exp_function::exp_function;
        double operator () (double x)
        {
            if (x < shift) return 0.0;
            return A*exp(B*(x - shift));
        }
    };
}


#endif // SIGNAL_HPP
