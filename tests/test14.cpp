#include "utils/table.hpp"
#include <cstdlib>


int main()
{
    utils::table t(5,5);

    t.names = {"a","ab","abc","abcd","abcde"};

    for (auto i = 0; i < t.rows; ++i)
        for (auto j = 0; j < t.columns; ++j)
            t.values[i][j] = std::to_string(rand()/double(RAND_MAX));

    t.print();

    for (auto i = 0; i < t.rows; ++i)
        for (auto j = 0; j < t.columns; ++j)
            t.values[i][j] = std::to_string(rand()); 
    t.print();

    // fill the table with appropriate data
    
    
    return 0;
}




