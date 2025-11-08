#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace utils {

    struct table
    {
        int columns = 0;
        int rows = 0;
        
        std::vector<std::string> names;
        std::vector<std::vector<std::string>> values;
        
        table(int columns = 0, int rows = 0) :columns(columns) , rows(rows)
        {
            names = std::vector<std::string>(columns);
            values = std::vector<std::vector<std::string>>(rows,std::vector<std::string>(columns));
        }
        
        template <typename Container>
        void add_row(Container c)
        {
            auto s = std::size(c);
            if (s >= columns) throw std::out_of_range("too many arguments for a row: " + std::to_string(s) + ", expected: " + std::to_string(columns));

            values.push_back(std::vector<std::string>(columns));

            for (auto i = 0;i < s;++i)
            {
                values.back()[i] = std::to_string(*(std::begin(c) + i));
            }

        }


        std::string get_string()
        {
            std::string out;

            out += top_names_string();
            out += names_string();
            out += bottom_names_string();
            for (auto i = 0 ; i < rows; ++i)
            {
                out += row_string_1(i);
                if (i != rows - 1)
                    out += row_string_intermediate();
            }
            out += bottom_string();
            return out;
        }

        void print()
        {
            std::cout << get_string();
        }

        private:

        std::size_t symbols_in_column(int index)
        {
            std::size_t size = 0;
            for (int i = 0; i < rows;++i)
            {
                size = std::max(size,values[i][index].size());
            }

            size = std::max(size,names[index].size());
            return size;
        }

        std::string top_names_string()
        {
            std::string row_str;
            row_str += "╔";
            for (auto j = 0; j < columns; ++j)
            {
                for (auto k = 0; k < symbols_in_column(j); ++k)
                    row_str += "═";
                if (j != columns - 1) row_str += "╤";
            }
            row_str += "╗\n";
            return row_str;
        }

        std::string bottom_names_string()
        {
            std::string row_str;
            row_str += "╠";
            for (auto j = 0; j < columns; ++j)
            {
                for (auto k = 0; k < symbols_in_column(j); ++k)
                    row_str += "═";
                if (j != columns - 1) row_str += "╪";
            }
            row_str += "╣\n";
            return row_str;
        }


        std::string bottom_string()
        {
            std::string row_str;
            row_str += "╚";
            for (auto j = 0; j < columns; ++j)
            {
                for (auto k = 0; k < symbols_in_column(j); ++k)
                    row_str += "═";
                if (j != columns - 1) row_str += "╧";
            }
            row_str += "╝\n";
            return row_str;
        }

        std::string names_string()
        {
            std::string row_str;
            row_str += "║";
            for (auto j = 0; j < columns; ++j)
            {
                std::string s(symbols_in_column(j) - names[j].size(),' ');
                s.append(names[j]);
                row_str += s;
                if (j != columns - 1)
                    row_str += "│";
            }
            row_str += "║\n";
            return row_str;
        }

        std::string row_string_1(int index)
        {
            std::string row_str;
            row_str += "║";
            for (auto j = 0; j < columns; ++j)
            {
                std::string s(symbols_in_column(j) - values[index][j].size(),' ');
                s.append(values[index][j]);
                row_str += s;
                if (j != columns -1)
                row_str += "│";
            }
            row_str += "║\n";
            return row_str;
        }

        std::string row_string_intermediate()
        {
            std::string str;
            str += "╟";
            for (auto j = 0; j < columns; ++j)
            {
                for (auto k = 0; k < symbols_in_column(j); ++k)
                    str += "─";
                if (j != columns - 1)    str += "┼";
            }

            str += "╢\n";
            return str;
        }


    };


}