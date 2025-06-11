#include "../graphics/raster.hpp"
#include <iostream>


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
    char s[100][100] = {};

    for (auto i = 0; i < 100; ++i)
    {
        for (auto j = 0; j < 100; ++j)
        {
            s[i][j] = ' ';
        }   
    }

    brezenhem_algorithm(10, 10, 90, 50, [&](auto x, auto y){s[x][y] = '*';});
    brezenhem_algorithm(10, 10, 50, 90, [&](auto x, auto y){s[x][y] = '*';});
    brezenhem_algorithm(90, 50, 50, 90, [&](auto x, auto y){s[x][y] = '*';});
    circle_raster(50, 50, 40, [&](auto x, auto y){s[x][y] = '*';});

    print_art(s, 100, 100);
}