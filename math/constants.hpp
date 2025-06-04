#pragma once

// #ifndef CONSTANTS_HPP
// #define CONSTANTS_HPP

namespace constants
{
    double constexpr pi         = 3.14159265358979323;
    double constexpr tau        = 3.14159265358979323 * 2.0;
    double constexpr half_pi    = 3.14159265358979323 * 0.5;

    double constexpr golden_ratio = 1.61803398874989484820;

    double constexpr e = 2.718'281'828'459'045'235'36;

    namespace phys
    {
        double constexpr speed_of_light     = 2.997'924'58e8;
        double constexpr elementary_charge  = 1.602'176'634e-19;
        double constexpr boltzman           = 1.380'649e-23;
        double constexpr planck             = 6.626'070'15e-34;
        double constexpr reduced_planck     = 6.626'070'15e-34 / tau;
        double constexpr avogadro           = 6.022'140'76e23;

        double constexpr electron_mass      = 9.109'383'713'928e-31;
        double constexpr proton_mass        = 1.672'621'925'955e-27;
        double constexpr neutron_mass       = 1.674'927'500'568e-27;

        double constexpr standard_atmosphere_pressure = 101'325;
        double constexpr standard_acceleration_of_free_fall = 9.806'65;


        // aliases
        double constexpr c          = speed_of_light;
        double constexpr h          = planck;
        double constexpr h_bar      = reduced_planck;
        double constexpr k          = boltzman;
        double constexpr Na         = avogadro;
        double constexpr m_e        = electron_mass;
        double constexpr m_p        = proton_mass;
        double constexpr m_n        = neutron_mass;

        double constexpr g          = standard_acceleration_of_free_fall;
    }
}

// #endif // CONSTANTS_HPP