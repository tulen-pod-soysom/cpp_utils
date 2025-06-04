
#include "signal_processing/signal.hpp"
#include "testing/sampling.hpp"
#include "testing/utils.hpp"
#include <fstream>
int main()
{
    sampler s;
    s.set_discretization_frequency(1000);

    auto v = s(10000,signal_processing::triangle_function{1,1,0});

    std::ofstream f("test.txt");

    for (auto i = v.begin(); i != v.end(); ++i)
    {
        f << *i << std::endl;
    }

    // utils::print(v,"",f);
}