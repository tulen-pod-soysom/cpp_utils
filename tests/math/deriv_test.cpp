
#include "math/function_derivative.hpp"
#include "testing/utils.hpp"
#include "utils/fast_plot.hpp"
#include "math/sampling.hpp"
#include <cmath>
#include <string>
#include <vector>
#include <format>



int main()
{
    auto a = adaptive_function_derivative([](double x){return std::sin(x);}, 0.0);

    utils::print(a,"sin(x) derivative: x = 1 ");
    utils::print(cos(0),"cos(x) value     : x = 1 ");
}