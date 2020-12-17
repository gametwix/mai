#include <iostream>
#include <vector>
#include "factory.hpp"
#include "Figure.hpp"
#include "Pentagon.hpp"
#include "Rhomb.hpp"

int main()
{
    std::vector<std::shared_ptr<Figure<int>>> vect;
    vect.push_back(Factory<int,Rhomb<int>>::CreatFig());
    for(int i=0;i<vect.size();++i)
        vect[i]->print();
    return 0;
}