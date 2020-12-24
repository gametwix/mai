#include <iostream>
#include <vector>
#include "ahok.hpp"

int main()
{
    TAhoKarasik ahk;
    std::vector<long long> a = {1,2,3,4,5};
    std::vector<long long> b = {1,2,6,7};
    ahk.Push(a);
    ahk.Push(b);
    return 0;	
}