#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <functional>
#include <iostream>
#include <numeric>
#include <ostream>
#include <utility>
#include <vector>


unsigned long long partial_factorial(int a, int b)
{
    unsigned long long m = 1;
    for (int i = a + 1; i <= b; ++i)
    {
        m *= i;
    }
    return m;
}


unsigned long long factorial(int n)
{
    return partial_factorial(1, n);
}


int number_of_combinations(int n, int k)
{
    if (k > n) return 0;

    int a = k;
    int b = n-k;

    if (a < b)
        std::swap(a,b);

    return partial_factorial(a, n)/factorial(b);
}


template <typename Function>
auto for_each_combination(int n, int k, Function f) {
  std::vector<int> init(k);
  std::iota(init.begin(), init.end(), 0);

  auto v = init;

  std::function<void(int)> sub_cycle = [&](int i) -> void {
    while (v[i] < init[i] + (n - k)) {
      v[i]++;
      if ((i < k - 1) && (i >= 0)) {
        sub_cycle(i + 1);
        continue;
      }
      f(v);
    }

    if (i > 0) {
      for (auto j = i; j < k; ++j)
        v[j] = v[j - 1] + 1;
    } else
      v[i] = 0;
  };

  f(v);
  for (int i = v.size() - 1; i >= 0; --i) {
    sub_cycle(i);
  }
}

#endif // COMBINATIONS_H