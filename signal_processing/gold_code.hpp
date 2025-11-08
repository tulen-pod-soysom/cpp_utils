#pragma once
#include <vector>
struct linear_feedback_shift_register
{
    explicit linear_feedback_shift_register(int size) :function_mask(size),values(size,1) {}
    explicit linear_feedback_shift_register(std::vector<bool> mask): function_mask(mask), values(mask.size(),1){}

    std::vector<bool> values;
    std::vector<bool> function_mask;

    auto process()
    {
        auto size = values.size();

        bool v = 0;
        for (auto i = 0; i < size; ++i) 
        {
            v ^= (values[i] && function_mask[i]);
        }

        bool out = values[size-1];
        for (int i = size-1; i > 0; i--)
        {
            values[i] = values[i-1];
        }   values[0] = v;

        return out;
    }

    auto process(int n)
    {
        std::vector<bool> v(n);
        for (auto i = 0; i < n; ++i)
            v[i] = process();
        return v;        
    }
};
