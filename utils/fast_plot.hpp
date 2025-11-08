#pragma once
#include "cpp_utils/graphics/gnuplot_helper.hpp"
#include <iterator>
namespace utils {
    template <typename Container>    
    void plot(Container c, std::string title = "")
    {
        gnuplot_program p;
        p.start();
        p.push_y_data(std::begin(c), std::end(c));
        p.script = "set title '" + title + "';" + p.script;
        p.push_script();
        p.stop();
    }

    template <typename Container1, typename Container2>    
    void plot_points(Container1 x, Container2 y, std::string title = "")
    {
        gnuplot_program p;
        p.start();
        p.script = "set title '" + title + "';" + p.script;
        // p.plot_y_data(std::begin(c), std::end(c));
        p.plot_points(std::begin(x), std::end(x), std::begin(y),std::end(y));
        p.stop();
    }

    template <typename Container1, typename Container2>    
    void draw_dots(Container1 x, Container2 y, std::string title = "")
    {
        gnuplot_program p;
        p.start();
        p.script = "set title '" + title + "'; plot '-' with points;\n";
        // p.plot_y_data(std::begin(c), std::end(c));
        p.plot_points(std::begin(x), std::end(x), std::begin(y),std::end(y));
        p.stop();
    }

}
