#pragma once

#include "Figure.hpp"
#include <iostream>
#include <utility>
#include <fstream>

template <typename T>
class Rhomb: public Figure<T>
{
protected:
    T Diag_1, Diag_2;
public:
    Rhomb(std::pair<T,T> C,T D1,T D2):Diag_1(D1),Diag_2(D2){
        this->Center.first = C.first;
        this->Center.second = C.second;
    }
    void print()
    override{
        std::pair<double,double> cords[4];
        for(int i = 0;i < 4;++i)
        {
            cords[i].first = this->Center.first;
            cords[i].second = this->Center.second;
        }

        cords[2].first  -=  (double)Diag_1/2;
        cords[0].first  +=  (double)Diag_1/2;
        cords[1].second -=  (double)Diag_2/2;
        cords[3].second +=  (double)Diag_2/2;

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