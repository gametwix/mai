#pragma once 

#include <iostream>
#include <utility>

template <typename T>
class Triangle
{
    private:
        using vertex_t = std::pair<T,T>;
        vertex_t Center;
        T Size;
    public:

        friend std::ostream& operator<< (std::ostream &out, const Triangle &triangle)
        {
            for(int i = 0;i < 3;++i)
            {
                out << "(" << triangle.dot[i].first << "," << triangle.dot[i].second << ") ";
            }
            return out;
        }

        friend std::istream& operator>>(std::istream &in, Triangle &triangle)
        {
            int size;
            in >> size;
            triangle.dot[1].first = size;
            triangle.dot[2].first = size/2;
            triangle.dot[2].second = (std::sqrt(3)/2)*;
            return in;
        }
};