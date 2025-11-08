#pragma once

#include <array>
namespace graphics
{
namespace affine
{

using point3d = std::array<double,3>;
using mat44 = std::array<std::array<double,4>,4>;

constexpr auto ortho_projectionXYZ(bool x = 1, bool y = 1, bool z = 1)
{
    return mat44{{
        {double(x),0,0,0},
        {0,double(y),0,0},
        {0,0,double(z),0},
        {0,0,0,1},
    }};
}

constexpr auto ortho_projectionXY(){return ortho_projectionXYZ(1,1,0);}
constexpr auto ortho_projectionXZ(){return ortho_projectionXYZ(1,0,1);}
constexpr auto ortho_projectionYZ(){return ortho_projectionXYZ(0,1,1);}





}
}