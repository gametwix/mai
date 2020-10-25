#include <iostream>
#include <vector>
#include "squere.hpp"
#include "rhomb.hpp"

int main()
{
    Squere a;
    std::vector<Figure*> l;
    Rhomb b;
    b.diag_2 = 5;
    b.diag_1 = 10;
    a.size = 5;

    a.Print_cord();
    std::cout << a.Area() << " "<< a.Center() << std::endl;
    return 0;
}