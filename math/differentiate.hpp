#include <assert.h>
#include <iterator>


namespace math
{

template <typename InputIt, typename OutputIt, typename Real = double>
void differentiate_central(InputIt begin, InputIt end, OutputIt output, Real step = 1.0)
{
    auto n = end - begin;
    assert(n > 2);

    *(output + 0) = -3* *(begin + 0) + 4 * *(begin + 1) - *(begin + 2);
    *(output + 0) /= 2 * step;

    for (auto i = 1; i < n - 1; ++i)
    {
        *(output + i) = (*(begin + i + 1) - *(begin + i - 1)) / 2.0 / step;
    }

    *(output + n - 1) = *(end - 1 - 2) - 4* *(end - 1 - 1) + 3* *(end - 1);
    *(output + n - 1) /= 2 * step;
}

template<typename Container,typename Real = double>
Container differentiate_central(Container a,Real step = 1.0)
{
    Container result(std::size(a));
    differentiate_central(std::begin(a),std::end(a),std::begin(result),step);
    return result;
}


template <typename InputIt, typename OutputIt, typename Real = double>
void differentiate_rightsided(InputIt begin, InputIt end, OutputIt output, Real step = 1.0)
{
    auto n = end - begin;
    assert(n > 2);

    *(output + 0) = -3* *(begin + 0) + 4 * *(begin + 1) - *(begin + 2);
    *(output + 0) /= 2 * step;

    for (auto i = 1; i < n - 1; ++i)
    {
        *(output + i) = (*(begin + i + 1) - *(begin + i)) / step;
    }

    *(output + n - 1) = *(end - 1 - 2) - 4* *(end - 1 - 1) + 3* *(end - 1);
    *(output + n - 1) /= 2 * step;
}

template<typename Container,typename Real = double>
Container differentiate_rightsided(Container a, Real step = 1.0)
{
    Container result(std::size(a));
    differentiate_rightsided(std::begin(a),std::end(a),std::begin(result));
    return result;
}

template <typename InputIt, typename OutputIt, typename Real = double>
void differentiate_leftsided(InputIt begin, InputIt end, OutputIt output, Real step = 1.0)
{
    auto n = end - begin;
    assert(n > 2);

    *(output + 0) = -3* *(begin + 0) + 4 * *(begin + 1) - *(begin + 2);
    *(output + 0) /= 2 * step;

    for (auto i = 1; i < n - 1; ++i)
    {
        *(output + i) = (*(begin + i) - *(begin + i-1)) / step;
    }

    *(output + n - 1) = *(end - 1 - 2) - 4* *(end - 1 - 1) + 3* *(end - 1);
    *(output + n - 1) /= 2 * step;
}

template<typename Container,typename Real = double>
Container differentiate_leftsided(Container a, Real step = 1.0)
{
    Container result(std::size(a));
    differentiate_leftsided(std::begin(a),std::end(a),std::begin(result));
    return result;
}

}
