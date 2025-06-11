#include "integrate.hpp"
#include "hooke_jeeves.hpp"
#include "differentiate.hpp"
#include "testing/signal_processing.hpp"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>
#include <armadillo>

template <typename T>
auto print(std::vector<T>& v, std::ostream& str = std::cout)
{
    for (auto i =0 ; i < v.size(); ++i) {
        str << v[i] << std::endl;
    }
}

using namespace arma;

int main()
{
//     auto f = [](std::vector<double> v)
//     {
//         auto& x = v[0];
//         auto& y = v[1];
//         auto& z = v[2];
//         // return sqr(v[0] - 1.2345) + sqr(v[1] + 3.134)  + sqr(v[2] - 65.45);
//         // if (abs(v[0]) < DBL_EPSILON ) return 1.0;
//         // return sin(v[0]) / v[0];
//
//         // return sqr(pow(v[0],5)  - v[0] + 1);
//         // return pow(1 - v[0],2) + 100*pow(v[1] - v[0]*v[0],2);
//
//         return pow(x*x+y-11,2) + pow(x + y*y - 7,2);
//     };
//
    // auto p = hooke_jeeves_optimizer(f, std::vector<double>{4.0,0.0,0.0},3,1e-10);
    // auto p = hooke_jeeves_optimizer_simple(f, std::vector<double>{2.0,-1.0,0.0},3,1e-5);
    // print(p);




    std::vector<double> v(16384);
    for (auto i =0 ; i < v.size(); ++i)
    {
        // v[i] = std::sin(-2*3.14159265358979323 * i / (256.));
        // v[i] = std::exp(-i);
        v[i] = 1.0;
    }
    
    std::cout << "simpson_integrate:\t" << simpson_integrate(v) << std::endl; 
    std::cout << "rectangle_integrate:\t" << rectangle_integrate(v) << std::endl; 
    std::cout << "trapeze_integrate:\t" << trapeze_integrate(v) << std::endl; 


    // vec v(1024);
    // vec d(1024);
    // for (auto i = 0; i < v.size(); ++i)
    //     // v(i) = sin(1e-8 * double(i));
    //     v(i) = sin(2*3.14159265358979323 * i/ double(v.size()));
    //     // v(i) = (i > 127)? 1:0;

    // differentiate(v.begin(),v.end() ,d.begin(),1e-8 );


    // d = v;

    // std::random_device rd;
    // for (auto i = 0; i < d.size(); ++i)
    // {
        // d(i) += std::normal_distribution<double>(0,0.1)(rd);
    // }

    // std::cout << MSE(v.begin(),v.end(),d.begin()) << std::endl;
    // std::cout << PSNR(MSE(v.begin(),v.end(),d.begin()),10) << std::endl;

    // std::ofstream str("out.txt");
    // str.precision(20);
    // d.print(str);

}
