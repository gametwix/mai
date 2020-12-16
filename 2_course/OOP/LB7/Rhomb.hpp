#pragma once

#include "Figure.hpp"
#include <iostream>
#include <utility>

template <typename T>
class Rhomb: public Figure<T>
{
protected:
    T Diag_1, Diag_2;
public:
    Rhomb(T C,T D1,T D2):Center(C),Diag_1(D1),Diag_2(D2){}
    void print()
    override{
        std::pair<double,double> cords[4];
        for(int i = 0;i < 4;++i)
        {
            cords[i].first = Center.first;
            cords[i].second = Center.second;
        }

        cords[2].first -= Diag_1/2;
        cords[0].first += Diag_1/2;
        cords[1].second -= Diag_2/2;
        cords[3].second += Diag_2/2;

        std::cout << "{";
        for(int i = 0;i < 4;++i)
            std::cout << "(" << cords[i].first << "," << cords[i].second << ")";  
        std::cout << "}";
    }

    void write(std::ofstream& file)
    override{
        file.write((const char*) &(this->Center.first), sizeof (T));
        file.write((const char*) &(this->Center.second), sizeof (T));
        file.write((const char*) &(this->Diag_1), sizeof (T));
        file.write((const char*) &(this->Diag_2), sizeof (T));
    }

};