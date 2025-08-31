#include <array>
#include <cstddef>
#include <stdexcept>

template <typename T, size_t s>
struct adaptive_resolution_vector : public std::array<T, s> {
private:
    size_t _size = 0;
    size_t _skip_counter = 0;
    size_t _skip_threshold = 1;  // Начинаем с пропуска каждой 2-й точки

public:
    void push_back(const T& value) {
        if (_size >= s) {
            // Сжимаем массив в 2 раза, оставляя каждую 2-ю точку
            for (size_t i = 0; i < s / 2; ++i) {
                (*this)[i] = (*this)[i * 2];
            }
            _size = s / 2;
            _skip_threshold *= 2;  // Увеличиваем порог пропуска
        }

        if (_skip_counter < _skip_threshold) {
            _skip_counter++;
            return;
        }

        (*this)[_size++] = value;
        _skip_counter = 0;
    }

    void clear() {
        _size = 0;
        _skip_counter = 0;
        _skip_threshold = 1;
    }

    size_t size() const { return _size; }
	// auto begin() const {return this->begin();}
	typename std::array<T,s>::iterator end() {return this->begin() + _size;}

    T& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of bounds");
        return std::array<T, s>::operator[](index);
    }
};

// template <typename T, size_t s>
// struct adaptive_resolution_vector : public std::array<T, s>
// {
// private:
// 	size_t skipped_inputs = 0;
// 	size_t _size = 0;
// 	size_t adapting_order = 0;
// public:

// 	adaptive_resolution_vector() : std::array<T, s>() {}

// 	void push_back(const T& value)
// 	{
// 		if (_size + 1 >= s / 2)
// 		{
// 			if (skipped_inputs < (1 << (adapting_order)) / 2)
// 			{
// 				skipped_inputs++;	return;
// 			}
// 			else skipped_inputs = 0;
// 		}

// 		if (_size + 1 >= s)
// 		{
// 			for (size_t i = 0; i < s / 2; i++)
// 			{
// 				(*this)[i] = (*this)[2 * i];
// 			}
// 			_size = s / 2;
// 			adapting_order++;
// 		}
// 		(*this)[_size++] = value;
// 	}

// 	void clear()
// 	{
// 		for (auto& i : *this)
// 		{
// 			i = {};
// 		}
// 		_size = 0;
// 	}

// 	size_t size() { return _size; }

// 	T& operator[] (size_t index)
// 	{
// 		if (index + 1 > _size) throw "out of bounds";
// 		return std::array<T, s>::operator[](index);
// 	}
// };