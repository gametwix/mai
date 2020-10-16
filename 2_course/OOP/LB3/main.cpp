#include <iostream>
#include "squere.hpp"

int main()
{
    Squere a(5);
    a.Print_cord();
    std::cout << a.Area() << " "<< a.Center() << std::endl;
    return 0;
}