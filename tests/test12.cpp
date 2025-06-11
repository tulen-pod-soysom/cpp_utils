#include "math/sampling.hpp"
#include "signal_processing/fft.hpp"
#include "signal_processing/signals.hpp"
#include "signal_processing/vector_operations.hpp"
#include "graphics/gnuplot_helper.hpp"
#include <algorithm>
#include <cfloat>
#include <cmath>

int main()
{
    auto x = SAMPLE_FUNCTION_MACRO(x, x, 0, 4096, 4096);
    auto v = signals::generate_sine(1024, 4096, 1, 256,0);
    v = vec_ops::add_const(v,-0.5);

    gnuplot_program p;

    p.start();
    p.plot_y_data(v.begin(), v.end());
    p.stop();

    v = vec_ops::abs(fft(v));
    v = vec_ops::to_dB(v,*std::max_element(v.begin(),v.end()));

    p.script = "plot '-' w l\n";

    p.start();
    p.plot_points(x.begin(), x.end(), v.begin(), v.end());
    p.stop();
    
}