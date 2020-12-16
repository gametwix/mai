#pragma once
#include <utility>
	
template <typename T>
class Figure
{
protected:
    std::pair<T,T> Center;

public:
    virtual void print() = 0;
    virtual void write(std::ofstream& file) = 0;
};//class Figure