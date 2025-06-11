#include "signal_processing/filter.hpp"
#include "math/fft.hpp"
#include "signal_processing/signal_processing.hpp"
#include "testing/utils.hpp"
#include <algorithm>
#include <complex>
#include <fstream>

int main()
{
    // std::vector<double> v = generate_highpass_sinc_filter(1024,128,1024);
    std::vector<double> v(2048);
    // std::vector<double> v = signal_processing::windows::triangle(1024);
    // for (auto& a : v) {
        // a /= 1024. / 2.0;
    // }
    v[0] = 1;
    // v[1] = -1;
    // v[2] = 1;
    // v[3] = -1;
    for (auto i = 512 - 64; i < 512 + 63; ++i)
    {
        // v[i] = 1;
    }


    // fir_filter f(generate_lowpass_sinc_filter(128,32,1024));
    iir_filter f(design_butterworth_low_pass_filter(30, 1024));

    for (auto i = 0; i < 111; ++i)
    {v = f(v); f.reset();}

    // std::rotate(v.begin(), v.begin() + 511, v.end());

    signal_processing::spectral_characteristics_to_file(v.begin(), v.end());
}