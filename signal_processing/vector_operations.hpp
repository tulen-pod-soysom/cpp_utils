#include <cmath>
#include <iterator>
namespace vec_ops {


template <typename InputIt, typename OutputIt>
void abs(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = std::abs(*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut abs(ContainerIn c)
{
  ContainerOut out(std::size(c));
  vec_ops::abs(std::begin(c),std::end(c),std::begin(out));
  return out;
}

template <typename InputIt, typename OutputIt>
void sqr(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = (*begin) * (*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut sqr(ContainerIn c)
{
  ContainerOut out(std::size(c));
  vec_ops::sqr(std::begin(c),std::end(c),std::begin(out));
  return out;
}


template <typename InputIt, typename OutputIt>
void negate(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = -(*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut negate(ContainerIn c)
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
ContainerOut sqrt(ContainerIn c)
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
ContainerOut log(ContainerIn c)
{
  ContainerOut out(std::size(c));
  vec_ops::log(std::begin(c),std::end(c),std::begin(out));
  return out;
}


template <typename InputIt, typename OutputIt>
void exp(InputIt begin, InputIt end, OutputIt output)
{
  while (begin != end) *output++ = std::exp(*begin++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut exp(ContainerIn c)
{
  ContainerOut out(std::size(c));
  vec_ops::exp(std::begin(c),std::end(c),std::begin(out));
  return out;
}


template <typename InputIt, typename OutputIt>
void atan2(InputIt begin1, InputIt end1,InputIt begin2, InputIt end2, OutputIt output)
{
  while (begin1 != end1 && begin2 != end2) *output++ = std::atan2(*begin1++,*begin2++);
}
template <typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut atan2(ContainerIn c1, ContainerIn c2)
{
  ContainerOut out(std::max(std::size(c1),std::size(c2)));
  vec_ops::atan2(std::begin(c1),std::end(c1),std::begin(c2),std::end(c2),std::begin(out));
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

template <typename Container> Container add(Container c1, Container c2) {
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

template <typename Container> Container sub(Container c1, Container c2) {
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

template <typename Container> Container mul(Container c1, Container c2) {
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

template <typename Container> Container div(Container c1, Container c2) {
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
double sum(Container c)
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
double mean(Container c)
{
  return mean(std::begin(c),std::end(c));
}


template <typename InputIt>
double energy(InputIt begin, InputIt end)
{
  double s = 0.0;
  while (begin != end) s += (*begin) * (*begin++);
  return s;
}

template <typename Container>
double energy(Container c)
{
  return energy(std::begin(c),std::end(c));
}


template <typename InputIt>
double norm(InputIt begin, InputIt end)
{
  double s = 0.0;
  while (begin != end) s += (*begin) * (*begin++);

  return std::sqrt(s);
}

template <typename Container>
double norm(Container c)
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
Container normalize(Container c1)
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
double error(Container c1, Container c2)
{
  return error(std::begin(c1),std::end(c1),std::begin(c2),std::end(c2)); 
}

} // namespace vec_ops