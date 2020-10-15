#include "squere.hpp"
#include <iostream>


double Squere::Area()
{
    return size*size;
}

void Squere::Print_cord()
{
    std::cout << "0,0 "<< size<<",0 " << size <<"," << size << " 0," << size << std::endl;
}

Dot Squere::Center()
{
    return Dot(size/2,size/2);
}