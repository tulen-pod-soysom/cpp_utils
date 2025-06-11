#include "signal_processing/fft.hpp"
#include "signal_processing/windows.hpp"
#include "signal_processing/vector_operations.hpp"
#include "testing/sampling.hpp"
#include "testing/utils.hpp"
#include <cmath>
#include <csignal>
#include <unistd.h>
#include "graphics/gnuplot_helper.hpp"

int main()
{
    auto v_y = SAMPLE_FUNCTION_MACRO(x, (x == 0? 1:sin(10*x)/10./x), -10*M_PI, 10*M_PI, 1024); 
    auto v_x = SAMPLE_FUNCTION_MACRO(x, x, -10*M_PI, 10*M_PI, 1024);

    auto v_y_1 = vec_ops::abs(fft(v_y,-1));

    v_y = vec_ops::mul(v_y,signal_processing::windows::Hamming(1024));
    auto v_y_2 = vec_ops::abs(fft(v_y,-1));

    {
        gnuplot_program p1;
        p1.script = "set grid; set autoscale noextend; set title \'Привет, грязный sinc!\';" + p1.script;
        p1.start();
        p1.plot_points(v_x.begin(), v_x.end(),v_y_1.begin(),v_y_1.end());
    }
    // sleep(3);

    gnuplot_program p2;
    p2.script = "set grid; set autoscale noextend; set title \'Привет, чистый sinc!\';" + p2.script;
    p2.start();
    p2.plot_points(v_x.begin(), v_x.end(),v_y_2.begin(),v_y_2.end());

    // utils::print(v);
}