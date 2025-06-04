#ifndef FFT_HPP
#define FFT_HPP

#include <algorithm>
#include <complex>
#include <iterator>
#include <vector>

template <typename InputIt, typename OutputIt>
void fft(InputIt begin, InputIt end, OutputIt out, double is) {
    int size = end - begin;
    if (size & size - 1)
        throw "size is not a power of two";
    static const double PI = 3.14159265358979323;

    // if (begin != out) {
    std::copy(begin, end, out);
    // }

    std::complex<double> temp, w, c;
    long i, j, istep;
    long m, mmax;
    long n = end - begin;
    double fn, r1, theta;
    fn = (double)n;
    double r = PI * is;

    j = 1;
    for (i = 1; i <= n; i++) {
        long i1 = i - 1;
        if (i < j) {
            int j1 = j - 1;
            std::swap(*(out + j1), *(out + i1));
        }
        m = n / 2;
        while (j > m) {
            j -= m;
            m = (m + 1) / 2;
        }
        j += m;
    }
    mmax = 1;
    while (mmax < n) {
        istep = 2 * mmax;
        r1 = r / (double)mmax;
        for (m = 1; m <= mmax; m++) {
            theta = r1 * (double)(m - 1);
            w = std::polar(1.0, theta);
            for (i = m - 1; i < n; i += istep) {
                j = i + mmax;
                c = *(out + j);
                temp = w * c;
                *(out + j) = *(out + i) - temp;
                *(out + i) = *(out + i) + temp;
            }
        }
        mmax = istep;
    }
    if (is > 0)
        for (i = 0; i < n; i++) {
            *(out + i) /= fn;
        }
};


template<typename ContainerIn, typename ContainerOut = ContainerIn>
ContainerOut fft(ContainerIn a, double iz)
{
    ContainerOut c (std::size(a));
    fft(std::begin(a),std::end(a),std::begin(c),iz);
    return c;
}


template<typename T>
std::vector<std::complex<T>> fft(std::vector<T> a, double iz)
{
    std::vector<std::complex<T>> c (std::size(a));
    fft(std::begin(a),std::end(a),std::begin(c),iz);
    return c;
}



template<typename InputIt>
std::complex<double> fourier(InputIt begin, InputIt end, double frequency, double is) {

    static const double PI = 3.14159265358979323;
    std::complex<double> result(0.0, 0.0);

    int N = end - begin;// data.size();

    for (int n = 0; n < N; ++n) {
        result += *(begin+n) * std::polar(1.0, is*2.0 * PI * frequency * n / N);
    }

    return result;
}


/*
template<typename T>
std::vector<T> abs(std::vector<T> v)
{
    for (auto& i : v) {
        i = std::abs(i);
    }
    return v;
}

template<typename T>
std::vector<T> abs(std::vector<std::complex<T>> v)
{
    std::vector<T> vv(std::size(v));
    for (auto i =0 ;i < vv.size(); ++i)
    {
        vv[i] = std::abs(v[i]);
    }
    return vv;
}

template<typename T>
std::vector<T> atan2(std::vector<std::complex<T>> v)
{
    std::vector<T> vv(std::size(v));
    for (auto i =0 ;i < vv.size(); ++i)
    {
        vv[i] = std::atan2(v[i].imag(),v[i].real());
    }
    return vv;
}*/

#endif //FFT_HPP
