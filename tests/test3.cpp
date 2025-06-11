#include <cmath>
#include "math/constants.hpp"
#include <math/differentiate.hpp>
#include <math/integrate.hpp>
#include <testing/utils.hpp>
#include <vector>

using math::differentiate_central;
using math::rectangle_integrate;
using math::trapeze_integrate;
using utils::print;

using namespace constants;

int main()
{
    std::vector<double> v(8,1.0);

    for (auto i = 0; i < v.size(); ++i) {
        v[i] = std::sin(tau * i / 8.);
    }

    print(v);
    print(differentiate_central(v, tau / 8.));
    print(rectangle_integrate(v, tau / 8.));
    print(rectangle_integrate(differentiate_central(v, tau / 8.), tau / 8.));
}