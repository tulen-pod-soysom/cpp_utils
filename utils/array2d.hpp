#pragma once

#include <vector>

template <typename T>
struct array2D
{
	using value_type = T;
 	using allocator_type = T;
 	using reference = T&;
 	using const_reference = const T&;
 	using size_type = size_t;
 	using difference_type = ptrdiff_t;

	size_t rows;
	size_t cols;

	std::vector<T> data;

	array2D(size_t rows = 0, size_t cols = 0): data(rows * cols), rows(rows), cols(cols){

	};

	T& operator()(int row, int col)
	{return data[cols * row + col];}

	auto& begin() {return data.begin();}
	auto& end() {return data.end();}

	auto& rbegin() {return data.rbegin();}
	auto& rend() {return data.rend();}

};


