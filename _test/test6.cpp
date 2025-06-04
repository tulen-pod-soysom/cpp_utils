#include "../signal_processing/filters.hpp"
#include "../testing/utils.hpp"
#include <fstream>
#include <vector>

int main()
{
    std::vector<double> s(256,0);
    std::vector<double> s2(256,0);

    s[0] = 1;
    // s[10] = 1 / 2.;
    // s[20] = 1 / 3.;
    // s[30] = 1 / 4.;
    // s[40] = 1 / 5.;
    // s[50] = 1 / 6.;

    iir_filter f;
    f.design_butterworth(200, 256, 4);

    f(s.begin(),s.end(),s2.begin());

    std::ofstream str("out.txt");
    utils::print(s2,"","\n",str);
}