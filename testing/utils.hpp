#ifndef UTILS_H
#define UTILS_H
#include <chrono>
#include <iostream>
#include <ostream>
#include <type_traits>
#include <vector>

namespace utils
{

template <typename T>
auto print(T a, std::string prefix = "", std::ostream &str = std::cout) 
{
    str << prefix;
    str << a;
    str << std::endl;
}

template <typename InputIt>
auto print(InputIt begin, InputIt end, std::string prefix = "", std::string separator = " ", std::ostream &str = std::cout) {
    str << prefix;
    for (auto i = begin; i != end; ++i)
        str << *i << separator;
    str << std::endl;
}

template <typename T>
auto print(std::vector<T> v, std::string prefix = "",std::string separator = " ",  std::ostream &str = std::cout) {
    print(std::begin(v),std::end(v),prefix,separator,str);
}



template <typename Function, typename Time_Step = std::chrono::milliseconds>
auto speed_benchmark(Function f, std::ostream& str = std::cout)
{
    std::chrono::system_clock clk;
    auto tp1 = clk.now();
    f();
    auto tp2 = clk.now();

    std::string postfix;

    if constexpr (std::is_same_v<Time_Step, std::chrono::seconds>)
    {
        postfix = " s";
    }
    else if constexpr (std::is_same_v<Time_Step, std::chrono::milliseconds>)
    {
        postfix = " ms";
    }
    else if constexpr (std::is_same_v<Time_Step, std::chrono::microseconds>)
    {
        postfix = " 𝛍s";
    }
    else if constexpr (std::is_same_v<Time_Step, std::chrono::nanoseconds>)
    {
        postfix = " ns";
    }

    str << "Time elapsed: " << std::chrono::duration_cast<Time_Step>(tp2 - tp1).count() << postfix << std::endl;
}


}
#endif // UTILS_H