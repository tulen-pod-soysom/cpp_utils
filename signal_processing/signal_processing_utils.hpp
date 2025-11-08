#ifndef SIGNAL_PROCESSING_UTILS_HPP
#define SIGNAL_PROCESSING_UTILS_HPP

#include "cpp_utils/math/sampling.hpp"
#include "cpp_utils/signal_processing/fft.hpp"
#include "cpp_utils/signal_processing/vector_operations.hpp"
#include "cpp_utils/signal_processing/windows.hpp"
#include "cpp_utils/graphics/gnuplot_helper.hpp"
#include <string>
#include <utility>
#include <vector>


namespace utils
{
template <typename InputIt>
void show_spectral_characteristics(InputIt begin, InputIt end,
                                   double sample_rate,
                                   bool plot_time_domain = true,
                                   bool plot_freq_domain = true,
                                   bool plot_phase = false,
                                   std::string window_type = "empty",
                                   bool apply_window = true,
                                   bool in_dB = true,
                                   bool fft_shift = true) 
{

    std::vector<double> c(begin,end);
    auto x = create_linspace(0,c.size()/ sample_rate,c.size());

    if (plot_time_domain)
    {
        gnuplot_program p;
        p.script = "set grid; set title \'Временное представление сигнала\'; set xlabel 'Время, с'; plot '-' w l\n";
        p.start();
        p.plot_points(x.begin(), x.end(), c.begin(),c.end());
        p.stop();
    }
    
    if (apply_window)
    {
        if (window_type == "hamming") c = vec_ops::mul(c,signal_processing::windows::Hamming(c.size()));
        if (window_type == "hann") c = vec_ops::mul(c,signal_processing::windows::Hann(c.size()));   
    }
    auto sp = fft(c);

    std::vector<double> f_x;
    if (fft_shift) 
    {
        for (auto i = 0; i < sp.size()/2; ++i) {std::swap(sp[i],sp[i + sp.size()/2]);}
        f_x = create_linspace(-sample_rate/2.0, sample_rate/2.0, c.size());
        
    }
    else {

        f_x = create_linspace(0, sample_rate, c.size());
        // f_x = SAMPLE_FUNCTION_MACRO(x, x, 0, sample_rate , c.size());
    }
    
    
    if (plot_freq_domain)
    {
        auto a = vec_ops::abs(sp);
        if (in_dB) a = vec_ops::to_dB(a,vec_ops::max(a));
        
        gnuplot_program p;

        p.script = in_dB? "set ylabel 'Амплитуда, дБ';" : "set ylabel 'Амплитуда';";
        p.script += "set grid; set title \'Амплитудный спектр сигнала\'; set xlabel 'Частота, Гц'; set autoscale noextend; plot '-' w l\n";
        p.start();
        p.plot_points(f_x.begin(), f_x.end(), a.begin(),a.end());
        p.stop();
    }
    
    if (plot_phase)
    {
        auto ph = vec_ops::atan2(sp);

        gnuplot_program p;
        p.script = "set grid; set title \'Фазовый спектр сигнала\'; set autoscale noextend; plot '-' w l\n";
        p.start();
        p.plot_points(f_x.begin(), f_x.end(), ph.begin(),ph.end());
        p.stop();
    }


}
}

#endif //SIGNAL_PROCESSING_UTILS_HPP
