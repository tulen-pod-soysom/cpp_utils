#include <iostream>
#include "../signal_processing/vector_operations.hpp"
#include "../utils/aliases.hpp"
#include "../testing/utils.hpp"

using namespace std::complex_literals;
using namespace vec_ops;

auto str_width_box(std::string s, size_t width)
{
	std::string out(width,' ');
	size_t size = std::min(s.size(),width);
	std::copy_n(s.begin(),size,out.begin());
	return out;
}


#define p(a) utils::print(a,str_width_box(#a + std::string(": "),22))

int main()
{
	vecd v1{1,2,3,4,5,6,7,8,9};
	auto v2 = v1;

	p(v1);
	p(v2);
	p(abs(v1));
	p(sqr(v1));
	p(add_const(v1,3));
	p(mul_const(v1,3));
	p(div_const(v1,3));
	p(negate(v1));
	p(sqrt(v1));
	p(log(v1));
	p(log10(v1));
	p(exp(v1));
	p(atan2(v1,v2));
	p(to_dB(v1));
	p(to_dB_power(v1));

	p(add(v1,v2));
	p(sub(v1,v2));
	p(mul(v1,v2));
	p(div(v1,v2));
	p(sum(v1));
	p(mean(v1));
	p(max(v1));
	p(min(v1));
	p(energy(v1));
	p(signal_power(v1));
	p(norm(v1));
	p(normalize(v1));
		
}
