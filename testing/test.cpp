#include "combinations.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>
#include "sampling.hpp"


// template <typename T>
// auto print(std::vector<T> &v, std::ostream &str = std::cout) {
//   for (auto i = v.begin(); i != v.end(); ++i)
//     str << *i << ' ';
//   str << std::endl;
// }

// int main()
// {
//     int n = 12;
//     int k = 10;

//     std::cin >> n >> k;

//     std::cout << number_of_combinations(n, k) << std::endl;

//     speed_benchmark(
//         [&] {
//              for_each_combination(n, k, [&](auto &v) { /*print<int>(v);*/ }); 
//              });
// }

int main()
{
    // std::vector<double> v(16);
    // sampler s;
    // s.set_discretization_frequency(16);
    // s.set_offset(0.25);
    
    // s(v.begin(),v.end(),[](auto x){return std::sin(2*3.14159265358979323*x);});

    sampler s;

    auto v = s(16,[](double x){return 1 / (x+1);});

    print(v);
}