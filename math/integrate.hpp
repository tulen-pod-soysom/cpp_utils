
#include <cassert>
#include <iterator>
#include <numeric>

namespace math
{

template<typename InputIt, typename Real = double>
auto simpson_integrate(InputIt begin, InputIt end, Real step = 1)
{
    assert((end - begin) % 2 == 0);

    Real s1 = 0.0;
    Real s2 = 0.0;

    for (auto i = begin + 2; i < end - 2; i += 2)
    {
        s1 += *i;
    }   s1 *= 2.0;

    for (auto i = begin + 1; i < end - 1; i += 2)
    {
        s2 += *i;
    }   s2 *= 4.0;

    return (*(begin) + *(end -1) + s1 + s2) * step / 3.0;
}

template <typename Container, typename Real = double>
auto simpson_integrate(Container a, Real step = 1)
{
    return simpson_integrate(std::begin(a),std::end(a),step);
}

template<typename InputIt, typename Real = double>
auto rectangle_integrate(InputIt begin, InputIt end, Real step = 1)
{
    return std::accumulate(begin,end,0.0) * step;
}

template <typename Container, typename Real = double>
auto rectangle_integrate(Container a, Real step = 1)
{
    return rectangle_integrate(std::begin(a),std::end(a),step);
}

template<typename InputIt, typename Real = double>
auto trapeze_integrate(InputIt begin, InputIt end, Real step = 1)
{
    return (*(begin) + 2*std::accumulate(begin + 1,end - 1,0.0) + *(end-1) )* step / 2.0;
}

template <typename Container, typename Real = double>
auto trapeze_integrate(Container a, Real step = 1)
{
    return trapeze_integrate(std::begin(a),std::end(a),step);
}

}
