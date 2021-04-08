//#include "SuffTree.hpp"

#include <iostream>
#include <memory>

int main(){
    std::shared_ptr<int> i;
    i = std::shared_ptr<int>(new int(3));
    i = std::shared_ptr<int>(new int(5));
    return 0;
}