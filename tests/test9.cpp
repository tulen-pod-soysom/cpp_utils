#include <chrono>
#include <cmath>
#include <graphics/gnuplot_helper.hpp>
#include <thread>
#include <vector>

int main()
{
    std::vector<double> v(1024);

    gnuplot_program p;
    p.start();


    static double beta = 1.0;
    while(true)
    {   
        for (auto i = 0; i < v.size(); ++i)
        {
            v[i] = sin(20*2*M_PI* i / 1024.) * exp(-beta*i/1024.);
        }

        p.plot_y_data(v.begin(), v.end());
        
        beta *= 1.1;
        beta = fmod(beta, 10.);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/10));
    }
}