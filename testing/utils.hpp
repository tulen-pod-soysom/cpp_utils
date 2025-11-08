#ifndef UTILS_H
#define UTILS_H
#include <chrono>
#include <initializer_list>
#include <iostream>
#include <map>
#include <ostream>
#include <type_traits>
#include <vector>
#include <concepts>
#include <utility>

namespace utils
{

// template <typename Container>
// concept is_container = requires(T t)
// {
//     std::begin(t);
//     std::end(t);
// };

template <typename T> 
// requires(!is_container<T>)
auto print(T a, std::string prefix = "", std::ostream &str = std::cout) 
{
    str << prefix;
    str << a;    
    str << std::endl;
}

// template <typename Container>
// auto print(Container c, std::string prefix = "", std::string separator = " ", std::ostream &str = std::cout)
// {
//     print(std::begin(c), std::end(c),prefix,separator,str);
// }


template <typename T,typename T_>
auto print(std::pair<T,T_> a, std::string prefix = "", std::string separator = " ", std::ostream &str = std::cout) 
{
    str << prefix;
    str << a.first << separator << a.second;
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
auto print(const std::vector<T>& v, std::string prefix = "",std::string separator = " ",  std::ostream &str = std::cout) {
    print(std::begin(v),std::end(v),prefix,separator,str);
}

template <typename T>
auto print(std::initializer_list<T> v, std::string prefix = "",std::string separator = " ",  std::ostream &str = std::cout) {
    print(std::begin(v),std::end(v),prefix,separator,str);
}


template <typename T,typename T_>
auto print(const std::map<T,T_>& v, std::string prefix = "",std::string separator = " ",  std::ostream &str = std::cout) {
    str << prefix;
	for (auto& it : v)
		str << it.first << separator << it.second << std::endl;
//    str << std::endl;
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
