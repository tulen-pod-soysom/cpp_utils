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
  auto set_sample_rate(double sample_rate){T = 1./sample_rate;}
  auto set_offset(double x) {offset = x;}
};

template<typename Expr,typename Container = std::vector<double>>
Container sample_expression(Expr F, double l, double r, size_t n)
{
  Container c(n);

  sampler s((r - l) / n, l);
  s(std::begin(c),std::end(c),F);
  return c;
}

#define SAMPLE_FUNCTION_MACRO(x,expr,l,r,n) sample_expression([=](auto x){return expr;},l,r,n)

template <typename OutputIt>
void create_linspace(OutputIt begin, OutputIt end, double l, double r, bool include_last = false)
{
  auto s = std::distance(begin,end);
  if (include_last) s = s - 1;

  int i = 0;
  while (begin != end) {*begin++ = l + (r - l) * i++ / double(s); }
}

template <typename Container = std::vector<double>>
Container create_linspace(double l, double r, int n, bool include_last = false)
{
  Container c(n);
  create_linspace(std::begin(c), std::end(c),l,r,include_last);
  return c;
}


#endif // SAMPLING_HPP