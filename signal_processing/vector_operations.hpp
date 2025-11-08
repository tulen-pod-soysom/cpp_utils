#pragma once
#include <algorithm>
#include <cmath>
#include <iterator>
#include <type_traits>
#include <vector>
#include <complex>
namespace vec_ops {


template <typename InputIt, typename OutputIt>
void abs(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = std::abs(*begin++);
}

template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut abs(const ContainerIn& c)
{
  ContainerOut out(std::size(c));
  vec_ops::abs(std::begin(c),std::end(c),std::begin(out));
  return out;
}

template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut abs(ContainerIn&& c)
{
  vec_ops::abs(std::begin(c),std::end(c),std::begin(c));
  return c;
}



template <typename = void>
std::vector<double> abs(std::vector<std::complex<double>> c)
{
  return abs<std::vector<std::complex<double>>,std::vector<double>>(c);
}


template <typename InputIt, typename OutputIt>
void sqr(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) {*output++ = (*begin) * (*begin); begin++;}
}

template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut sqr(const ContainerIn& c)
{
  ContainerOut out(std::size(c));
  vec_ops::sqr(std::begin(c),std::end(c),std::begin(out));
  return out;
}


template <typename InputIt, typename OutputIt, typename ConstType = typename std::iterator_traits<InputIt>::value_type>
void add_const(InputIt begin, InputIt end, ConstType c, OutputIt output)
{
  while (begin != end) *output++ = (*begin++) + c;
}
template <typename ContainerIn, typename ConstType, typename ContainerOut = ContainerIn>
ContainerOut add_const(const ContainerIn& c, ConstType value)
{
  ContainerOut out(std::size(c));
  vec_ops::add_const(std::begin(c),std::end(c),value,std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt, typename ConstType = typename std::iterator_traits<InputIt>::value_type>
void mul_const(InputIt begin, InputIt end, ConstType c, OutputIt output)
{
  while (begin != end) *output++ = (*begin++) * c;
}
template <typename ContainerIn, typename ConstType, typename ContainerOut = ContainerIn>
ContainerOut mul_const(const ContainerIn& c, ConstType value)
{
  ContainerOut out(std::size(c));
  vec_ops::mul_const(std::begin(c),std::end(c),value,std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt, typename ConstType = typename std::iterator_traits<InputIt>::value_type>
void div_const(InputIt begin, InputIt end, ConstType c, OutputIt output)
{
  while (begin != end) *output++ = (*begin++) / c;
}
template <typename ContainerIn, typename ConstType, typename ContainerOut = ContainerIn>
ContainerOut div_const(const ContainerIn& c, ConstType value)
{
  ContainerOut out(std::size(c));
  vec_ops::div_const(std::begin(c),std::end(c),value,std::begin(out));
  return out;
}


template <typename InputIt, typename OutputIt>
void negate(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) {*output++ = -(*begin); begin++;}
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut negate(const ContainerIn& c)
{
  ContainerOut out(std::size(c));
  vec_ops::abs(std::begin(c),std::end(c),std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt>
void sqrt(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = std::sqrt(*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut sqrt(const ContainerIn& c)
{
  ContainerOut out(std::size(c));
  vec_ops::sqrt(std::begin(c),std::end(c),std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt>
void log(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = std::log(*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut log(const ContainerIn& c)
{
  ContainerOut out(std::size(c));
  vec_ops::log(std::begin(c),std::end(c),std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt>
void log10(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = std::log10(*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut log10(const ContainerIn& c)
{
  ContainerOut out(std::size(c));
  vec_ops::log10(std::begin(c),std::end(c),std::begin(out));
  return out;
}


template <typename InputIt, typename OutputIt>
void exp(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = std::exp(*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut exp(const ContainerIn& c)
{
  ContainerOut out(std::size(c));
  vec_ops::exp(std::begin(c),std::end(c),std::begin(out));
  return out;
}

template <typename T>
std::vector<double> real(std::vector<std::complex<T>> v)
{
  std::vector<double> r(v.size());
  for (auto i = 0; i < v.size(); ++i) r[i] = v[i].real();
  return r;
}

template <typename T>
std::vector<double> imag(std::vector<std::complex<T>> v)
{
  std::vector<double> r(v.size());
  for (auto i = 0; i < v.size(); ++i) r[i] = v[i].imag();
  return r;
}



template <typename InputIt, typename OutputIt>
void atan2(InputIt begin1, InputIt end1,InputIt begin2, InputIt end2, OutputIt output)
{
  while (begin1 != end1 && begin2 != end2) *output++ = std::atan2(*begin1++,*begin2++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut atan2(const ContainerIn& c1, const ContainerIn& c2)
{
  ContainerOut out(std::max(std::size(c1),std::size(c2)));
  vec_ops::atan2(std::begin(c1),std::end(c1),std::begin(c2),std::end(c2),std::begin(out));
  return out;
}

template <typename T>
std::vector<double> atan2(std::vector<std::complex<T>> v)
{
  auto r = real(v);
  auto i = imag(v);

  std::vector<double> c(v.size());
  atan2(i.begin(),i.end(),r.begin(),r.end(),c.begin());
  return c;
}




template <typename InputIt, typename OutputIt>
void to_dB(InputIt begin, InputIt end, OutputIt output, double reference = 1)
{
  while (begin != end) *output++ = 10*(std::log10(*begin++) - std::log10(reference)) ;
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut to_dB(const ContainerIn& c, double reference = 1)
{
  ContainerOut out(std::size(c));
  vec_ops::to_dB(std::begin(c),std::end(c),std::begin(out),reference);
  return out;
}

template <typename InputIt, typename OutputIt>
void to_dB_power(InputIt begin, InputIt end, OutputIt output, double reference = 1)
{
  while (begin != end) *output++ = 20*(std::log10(*begin++) - std::log10(reference)) ;
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut to_dB_power(const ContainerIn& c, double reference = 1)
{
  ContainerOut out(std::size(c));
  vec_ops::to_dB_power(std::begin(c),std::end(c),std::begin(out),reference);
  return out;
}



template <typename InputIt, typename OutputIt>
void add(InputIt begin1, InputIt end1, InputIt begin2, InputIt end2,
         OutputIt output) {
  while (begin1 != end1 && begin2 != end2) {
    *output++ = *begin1++ + *begin2++;
  }
  while (begin1 != end1) {
    *output++ = *begin1++;
  }
  while (begin2 != end2) {
    *output++ = *begin2++;
  }
}

template <typename Container> Container add(const Container& c1, const Container& c2) {
  Container out(std::max(std::size(c1), std::size(c2)));
  add(std::begin(c1), std::end(c1), std::begin(c2), std::end(c2),
      std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt>
void sub(InputIt begin1, InputIt end1, InputIt begin2, InputIt end2,
         OutputIt output) {
  while (begin1 != end1 && begin2 != end2) {
    *output++ = *begin1++ - *begin2++;
  }
  while (begin1 != end1) {
    *output++ = *begin1++;
  }
  while (begin2 != end2) {
    *output++ = -*begin2++;
  }
}

template <typename Container> Container sub(const Container& c1, const Container& c2) {
  Container out(std::max(std::size(c1), std::size(c2)));
  sub(std::begin(c1), std::end(c1), std::begin(c2), std::end(c2),
      std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt>
void mul(InputIt begin1, InputIt end1, InputIt begin2, InputIt end2,
         OutputIt output) {
  while (begin1 != end1 && begin2 != end2) {
    *output++ = *begin1++ * *begin2++;
  }
  while (begin1 != end1) {
    *output++ = 0;
  }
  while (begin2 != end2) {
    *output++ = 0;
  }
}

template <typename Container> Container mul(const Container& c1, const Container& c2) {
  Container out(std::max(std::size(c1), std::size(c2)));
  mul(std::begin(c1), std::end(c1), std::begin(c2), std::end(c2),
      std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt>
void div(InputIt begin1, InputIt end1, InputIt begin2, InputIt end2,
         OutputIt output) {

  if (std::distance(begin1, end1) != std::distance(begin2, end2))
    throw std::invalid_argument("Mismatched sizes in divide()");
  while (begin1 != end1 && begin2 != end2) {
    *output++ = *begin1++ / *begin2++;
  }
}

template <typename Container> Container div(const Container& c1, const Container& c2) {
  Container out(std::max(std::size(c1), std::size(c2)));
  div(std::begin(c1), std::end(c1), std::begin(c2), std::end(c2),
      std::begin(out));
  return out;
}


template <typename InputIt>
double sum(InputIt begin, InputIt end)
{
  double s = 0.0;
  while (begin != end) s += *begin++;
  return s;
}

template <typename Container>
double sum(const Container& c)
{
  return sum(std::begin(c),std::end(c));
}

template <typename InputIt>
double mean(InputIt begin, InputIt end)
{
  double s = 0.0; double m = std::distance(begin,end);
  while (begin != end) s += *begin++;
  return s / m;
}

template <typename Container>
double mean(const Container& c)
{
  return mean(std::begin(c),std::end(c));
}

template <typename InputIt>
typename std::iterator_traits<InputIt>::value_type max(InputIt begin, InputIt end)
{
  return *std::max_element(begin,end);
}

template <typename Container>
double max(const Container& c)
{
  return vec_ops::max(std::begin(c),std::end(c));
}

template <typename InputIt>
typename std::iterator_traits<InputIt>::value_type min(InputIt begin, InputIt end)
{
  return *std::min_element(begin,end);
}

template <typename Container>
double min(const Container& c)
{
  return vec_ops::min(std::begin(c),std::end(c));
}


template <typename InputIt>
double energy(InputIt begin, InputIt end)
{
  double s = 0.0;
  while (begin != end) {s += std::norm(*begin); begin++;}
  return s;
}

template <typename Container>
double energy(const Container& c)
{
  return energy(std::begin(c),std::end(c));
}

template <typename InputIt>
double signal_power(InputIt begin, InputIt end)
{
  return energy(begin,end) / (double) std::distance(begin,end);
}
template <typename Container>
double signal_power(const Container& c)
{
  return signal_power(std::begin(c),std::end(c));
}


template <typename InputIt>
double norm(InputIt begin, InputIt end)
{
  double s = 0.0;
  while (begin != end) s += (*begin) * (*begin++);

  return std::sqrt(s);
}

template <typename Container>
double norm(const Container& c)
{
  return norm(std::begin(c),std::end(c));
}

template <typename InputIt, typename OutputIt>
void normalize(InputIt begin, InputIt end, OutputIt output)
{
  double n = norm(begin,end);

  while (begin != end) *output++ = *begin++ / n;
}

template <typename Container>
Container normalize(const Container& c1)
{
  Container out(std::size(c1));
  normalize(std::begin(c1),std::end(c1),std::begin(out));
  return out;
}

template <typename InputIt>
double error(InputIt begin1, InputIt end1, InputIt begin2, InputIt end2)
{
  double e = 0.0;

  while (begin1 != end1 && begin2 != end2) {
    e += (*begin1 - *begin2) * (*begin1++ - *begin2++);
  }
  return e;
}

template <typename Container>
double error(const Container& c1, const Container& c2)
{
  return error(std::begin(c1),std::end(c1),std::begin(c2),std::end(c2)); 
}


template <typename Container>
auto cross_correlation_k(const Container& c1, const Container& c2,int k_offset)
{
  using Type = std::decay_t<typeof(*c1.begin())>;

  Type s = 0.0;
  for (int i = 0; i < c1.size(); ++i)
  {
    if ((i+k_offset > c2.size()-1) || (i+k_offset) < 0) continue;
    s += c1[i]*std::conj(c2[i+k_offset]);
  }
  return s;
}

template <typename Container>
auto cross_correlation(const Container& c1, const Container& c2, int l, int r)
{
  size_t result_size = std::abs(r - l);
  Container result(result_size);

  for (auto i = 0; i < result_size; ++i)
    result[i] = cross_correlation_k(c1, c2, l + i);

  return result;
}

template <typename Container>
auto cross_correlation(const Container& c1, const Container& c2)
{
  return cross_correlation(c1,c2,-c1.size(),c2.size());
}


template <typename Container>
auto cross_correlation_normalized(const Container& c1, const Container& c2, int l, int r)
{
  return div_const(cross_correlation(c1,c2,l,r) , std::sqrt(energy(c1)*energy(c2)));
}

template <typename Container>
auto cross_correlation_normalized(const Container& c1, const Container& c2)
{
  return cross_correlation_normalized(c1,c2,-c1.size(),c2.size());
}


template <typename InputIt, typename OutputIt>
void cycle_shift(InputIt begin, InputIt end, OutputIt output, int n)
{
  // TODO:
}

template <typename InputIt, typename OutputIt>
void container_xor(InputIt begin1, InputIt end1, InputIt begin2, InputIt end2, OutputIt output)
{
   while (begin1 != end1 && begin2 != end2) {
    *output++ = *begin1++ ^ *begin2++;
  }
  // while (begin1 != end1) {
    // *output++ = 0;
  // }
  // while (begin2 != end2) {
    // *output++ = 0;
  // }
}

template <typename Container>
Container container_xor(Container a, Container b)
{
  Container c(std::max(std::size(a),std::size(b)));
  container_xor(std::begin(a),std::end(a),std::begin(b),std::end(b),std::begin(c));
  return c;
}


} // namespace vec_ops
