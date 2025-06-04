
#include <type_traits>
template <typename T, typename Container>
struct periodic_operator
{
    Container& source;

    // T left;
    // T right;
    T width;
    T height;

    auto operator() (T i, T j)
    {
        if constexpr (std::is_integral_v<T>)
        {
            i = i % width;
            j = j % height;
        }
        else if constexpr (std::is_floating_point_v<T>) {
            
        }

        return source(i,j);
    }
};