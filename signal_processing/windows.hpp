
#include <cmath>
#include <iterator>
#include <vector>
namespace signal_processing
{

    namespace windows
    {
        template<typename OutputIt>
        void triangle(OutputIt begin, OutputIt end)
        {
            auto s = std::distance(begin,end);

            for (auto i = 0; i < s; ++i)
            {
                *(begin + i) = (1 - 2 * std::abs(i - s/2.0)/s);
            }
        }

        template <typename ContainerOut = std::vector<double>>
        ContainerOut triangle(size_t n)
        {
            ContainerOut c(n);
            triangle(std::begin(c),std::end(c));
            return c;
        }

        template<typename OutputIt>
        void Hann(OutputIt begin, OutputIt end)
        {
            auto s = std::distance(begin,end);

            for (auto i = 0; i < s; ++i)
            {
                *(begin + i) = 0.5 - 0.5 * cos(2 * M_PI * i / double(s - 1));
            }
        }

        template <typename ContainerOut = std::vector<double>>
        ContainerOut Hann(size_t n)
        {
            ContainerOut c(n);
            Hann(std::begin(c),std::end(c));
            return c;
        }

        template<typename OutputIt>
        void Hamming(OutputIt begin, OutputIt end)
        {
            auto s = std::distance(begin,end);

            for (auto i = 0; i < s; ++i)
            {
                *(begin + i) = 0.53836 - 0.46164 * cos(2 * M_PI * i / double(s - 1));
            }
        }

        template <typename ContainerOut = std::vector<double>>
        ContainerOut Hamming(size_t n)
        {
            ContainerOut c(n);
            Hamming(std::begin(c),std::end(c));
            return c;
        }

        template<typename OutputIt>
        void Gauss(OutputIt begin, OutputIt end, double sigma = 0.4)
        {
            auto s = std::distance(begin,end);

            for (auto i = 0; i < s; ++i)
            {
               auto v = (i-s/2.0)/(sigma * s / 2.0);
                *(begin + i) = std::exp(-0.5*v*v);
            }
        }

        template <typename ContainerOut = std::vector<double>>
        ContainerOut Gauss(size_t n, double sigma = 0.4)
        {
            ContainerOut c(n);
            Gauss(std::begin(c),std::end(c), sigma);
            return c;
        }

    }


// double FilterProgram::WindowFunc(double width, double t, WindowType wt)
// {
//     if (fabs(t) > width/2) return 0.0;
//     double t_ = t / width;
//     switch (wt)
//     {
//         case WindowType::Rectangle: return 1.0; break;
//         case WindowType::Triangle:  return 2*(1 - 2 * fabs(t_)); break;
//         case WindowType::Hann:      return 2*(0.5 * (1 + cos(2*PI*t_)) ); break;
//         case WindowType::Hamming:   return 1.85185*(0.54 + 0.46 * cos(2*PI*t_)); break;
//         case WindowType::Gauss:     return 2.01979*exp(-0.5*(2*2.5*t_)*(2*2.5*t_)); break;
//     }
// }
}