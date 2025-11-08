#include <cstdio>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <string>

struct gnuplot_program
{
    std::unique_ptr<FILE> pipe;

    std::string gnuplot_path = "gnuplot";
    std::string script = "plot $DATA0 with lines \n";

    std::set<int> data_indexes;

    void start()
    {
        pipe.reset(popen((gnuplot_path + " -p").c_str(),"w"));
        if(pipe == nullptr) {std::cout << "Gnuplot doesn't startup!" << std::endl;}
    }

    void push_script()
    {
        fprintf(pipe.get(), "%s", script.c_str());
    }

    template <typename InputIt>
    void push_y_data(InputIt begin, InputIt end, int index = 0)
    {
        fprintf(pipe.get(), "$DATA%i << EOD\n",index);

        for (auto it = begin; it != end; ++it)
            fprintf(pipe.get(), "%f\n",*it);
        fprintf(pipe.get(), "EOD\n");

        data_indexes.emplace(index);
    }
    template <typename Container>
    void push_y_data(Container c, int index = 0)
    {
        push_y_data(std::begin(c),std::end(c),index);
    }


    template <typename InputIt>
    void plot_points(InputIt begin_x, InputIt end_x, InputIt begin_y, InputIt end_y, int index = 0)
    {
        fprintf(pipe.get(), "$DATA%i << EOD\n",index);

        auto it_y = begin_y;
        for (auto it_x = begin_x; it_x != end_x; ++it_x, ++it_y)
        {
            fprintf(pipe.get(), "%f %f\n",*it_x, *it_y);
        }
        fprintf(pipe.get(), "EOD\n");
    }
    template <typename ContainerX, typename ContainerY>
    void plot_points(ContainerX x, ContainerY y, int index = 0)
    {
        plot_points(std::begin(x),std::end(x),std::begin(y),std::end(y),index);
    }

    void replot() 
    {
        fprintf(pipe.get(), "replot\n");
    }

    void stop()
    {
        fclose(pipe.get());
        pipe.release();
    }

    ~gnuplot_program()
    {
    }
};
