#pragma once
#include <utility>
 
template <typename T>
class Figure{
public:
 std::pair<T,T> Center;
 virtual void print() = 0;
 virtual void write(std::string name) = 0;
};//class Figure