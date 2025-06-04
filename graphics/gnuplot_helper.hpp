#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

struct gnuplot_program
{
    std::unique_ptr<FILE> pipe;

    std::string gnuplot_path = "gnuplot";
    std::string script = "plot '-' with lines \n";

    void start()
    {
        pipe.reset(popen((gnuplot_path + " -p").c_str(),"w"));
        if(pipe == nullptr) {std::cout << "Gnuplot doesn't startup!" << std::endl;}
    }

    template <typename InputIt>
    void plot_y_data(InputIt begin, InputIt end)
    {
        fprintf(pipe.get(), "%s", script.c_str());
        for (auto it = begin; it != end; ++it)
            fprintf(pipe.get(), "%f\n",*it);
        fprintf(pipe.get(), "e\n");
        // fprintf(pipe.get(), "pause mouse close\n");
    }

    void replot() 
    {
        fprintf(pipe.get(), "replot\n");
    }

    ~gnuplot_program()
    {
        fclose(pipe.get());
        pipe.reset();
    }
};
