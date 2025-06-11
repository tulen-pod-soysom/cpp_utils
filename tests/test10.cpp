#include "signal_processing/vector_operations.hpp"
#include "testing/utils.hpp"
#include <algorithm>
#include <random>
#include <vector>

void test_vectors(std::vector<double> v1, std::vector<double> v2)
{
    utils::print(v1,"v1: ");
    utils::print(v2,"v2: ");
    utils::print("");

    utils::print(vec_ops::add(v1,v2),"add: ");
    utils::print(vec_ops::sub(v1,v2),"sub: ");
    utils::print(vec_ops::mul(v1,v2),"mul: ");
    utils::print(vec_ops::div(v1,v2),"div: ");
    utils::print("");

    utils::print(vec_ops::negate(v1),"negate: ");
    utils::print(vec_ops::abs(v1),"abs: ");
    utils::print(vec_ops::sqr(v1),"sqr: ");
    utils::print(vec_ops::sqrt(v1),"sqrt: ");
    utils::print(vec_ops::log(v1),"log: ");
    utils::print(vec_ops::exp(v1),"exp: ");
    utils::print(vec_ops::atan2(v1,v2),"atan2: ");
    utils::print("");

    utils::print(vec_ops::sum(v1),"sum: ");
    utils::print(vec_ops::mean(v1),"mean: ");
    utils::print(vec_ops::norm(v1),"norm: ");
    utils::print(vec_ops::energy(v1),"energy: ");
    utils::print(vec_ops::normalize(v1),"normalize: ");
    utils::print(vec_ops::norm(vec_ops::normalize(v1)),"normalized norm: ");

    utils::print(vec_ops::error(v1,v2),"error: ");
}



int main()
{
    // std::vector v1{1.,2.,3.,4.,5.,-1.,-2.,-3.,-4.,-5.};
    // std::vector v2{-1.,-2.,-3.,-4.,-5.,1.,2.,3.,4.,5.};

    std::vector<double> v1(5);
    std::vector<double> v2(5);

    std::random_device rd;
    std::uniform_real_distribution<double> dist(-5,5);

    std::generate_n(v1.begin(),v1.size(),[&]{return dist(rd);});
    std::generate_n(v2.begin(),v2.size(),[&]{return dist(rd);});

    utils::speed_benchmark([&]{test_vectors(v1, v2);});
}