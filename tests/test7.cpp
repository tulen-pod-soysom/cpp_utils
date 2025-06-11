#include "testing/bit_packing.hpp"
#include "testing/utils.hpp"
#include <vector>


int main()
{
    std::vector v{1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0};
    utils::print(v);

    auto v2 = pack_bits_N_to_M(1,8,v);
    v = pack_bits_N_to_M(8,1,v2);

    utils::print(v2);
    utils::print(v);
}