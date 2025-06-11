
#include "signal_processing/signal_processing_utils.hpp"
#include "signal_processing/signals.hpp"
#include <algorithm>
#include <cfloat>
#include <cmath>

int main()
{
    auto v1 = signals::generate_triangle(1024, 1024, 1, 5);
    // v = vec_ops::add(v, signals::generate_white_noise(1024, 0.0001));
    // v = vec_ops::add_const(v,-0.5);
    auto v2 = signals::generate_sine(1024, 1024, -1, 100,0);
    // auto v2 = signals::generate_meandr(1024, 4096, 0, 110,0);
    auto v = vec_ops::mul(v1,v2);

    utils::show_spectral_characteristics(v.begin(), v.end(), 1024, true,
                                         true, false, "hamming",false,true, true);
}