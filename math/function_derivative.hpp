


#include <cfloat>
#include <cstdlib>
template <typename Function, typename T = double>
T function_derivative(Function f, double x, double h = 1e-8)
{
    return (f(x + h) - f(x - h)) / (2 * h);
}

template <typename Function, typename T = double>
T adaptive_function_derivative(Function f, double x, double precision = DBL_EPSILON, double h = 1e-8)
{
    auto f1 = function_derivative(f, x, h);
    auto f2 = f1;

    do {
        f1 = f2;

        h /= 2.0;
        f2 = function_derivative(f, x, h);
    } while (std::abs(f2 - f1) >= precision);

    return f2;
}


