#include "../graphics/raster.hpp"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ratio>
#include <thread>


template<typename T>
void print_art(T s, int w, int h)
{
    for (auto i = h-1; i != 0; --i)
    {   
        for (auto j = 0; j < w; ++j)
        {
            std::cout << s[i][j];
        }   std::cout << std::endl;
    }
}

int main()
{
    double t = 0;
    while (true)
    {
        system("clear");
        char s[100][200] = {};

        for (auto i = 0; i < 100; ++i)
        {
            for (auto j = 0; j < 200; ++j)
            {
                s[i][j] = ' ';
            }   
        }

        circle_raster(50, 50, 40, [&](auto x, auto y){s[x][y] = '*';});

        
        auto x1 = 50 + 40*cos(t);
        auto y1 = 50 + 40*sin(t);

        auto x1_opp = 50 - 30*cos(t);
        auto y1_opp = 50 - 30*sin(t);


        auto x2 = 50 + 40*cos(t + 2*M_PI/3.0);
        auto y2 = 50 + 40*sin(t + 2*M_PI/3.0);
        
        auto x3 = 50 + 40*cos(t + 2*2*M_PI/3.0);
        auto y3 = 50 + 40*sin(t + 2*2*M_PI/3.0);


        circle_raster(x1, y1, 40, [&](auto x, auto y){if ((x-50)*(x-50) + (y-50)*(y-50) > 20*20) return; s[x][y] = '*';});
        circle_raster(x1_opp, y1_opp, 40, [&](auto x, auto y){if ((x-50)*(x-50) + (y-50)*(y-50) > 20*20) return; s[x][y] = '*';});

        brezenhem_algorithm(50, 150, x1, y1, [&](auto x, auto y){s[x][y] = '*';});
        brezenhem_algorithm(50, 150, x2, y2, [&](auto x, auto y){s[x][y] = '*';});
        brezenhem_algorithm(50, 150, x3, y3, [&](auto x, auto y){s[x][y] = '*';});
        brezenhem_algorithm(x1, y1, x2, y2, [&](auto x, auto y){s[x][y] = '*';});
        brezenhem_algorithm(x1, y1, x3, y3, [&](auto x, auto y){s[x][y] = '*';});
        brezenhem_algorithm(x3, y3, x2, y2, [&](auto x, auto y){s[x][y] = '*';});

        print_art(s, 200, 100);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));
        t += 1/30.;
    }
}