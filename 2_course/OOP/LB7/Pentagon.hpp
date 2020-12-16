#pragma once

#include "Figure.hpp"
#include <iostream>
#include <utility>

#define PI 3.1415926
template <typename T>
class Pentagon: public Figure<T>
{
protected:
    T Size;
public:
    void print()
    override{
        std::pair<double,double> cords[5];
        double R = sqrt(10)*sqrt(5+sqrt(5)))*Size/10
        for(int i = 0;i < 5;++i)
        {
            cords[i].first = Center.first;
            cords[i].second = Center.second;
            cords[i].first +=R*cos(2*Pi*i/5); 
            cords[i].first +=R*sin(2*Pi*i/5);
        }

        std::cout << "{";
        for(int i = 0;i < 5;++i)
            std::cout << "(" << cords[i].first << "," << cords[i].second << ")";  
        std::cout << "}";
    }

    void write(std::ofstream& file)
    override{
        file.write((const char*) &(this->Center.first), sizeof (T));
        file.write((const char*) &(this->Center.second), sizeof (T));
        file.write((const char*) &(this->Size), sizeof (T));
    }

    
};