#ifndef SAMPLING_HPP
#define SAMPLING_HPP
#include <vector>

struct sampler {
  sampler(double T = 1, double offset = 0) :T(T),offset(offset){}

  double T = 1;
  double offset = 0;

  template <typename Function, typename OutputIt>
  auto operator()(OutputIt begin, OutputIt end, Function f) {
    int i = 0;
    for (auto it = begin; it != end; ++it,++i)
    {
        *it = f(i*T + offset);
    }
  }

  template <typename Function>
  auto operator()(unsigned size, Function f)
  {
    using T_ = typeof(f(0.0));
    std::vector<T_> v(size);

    for (auto i = 0; i < size; ++i)
    {
      v[i] = f(i*T + offset);
    }
    return v;
  }

  auto set_period(double t) { T = t; }
  auto set_discretization_frequency(double fd){T = 1./fd;}
  auto set_offset(double x) {offset = x;}
};

#endif // SAMPLING_HPP