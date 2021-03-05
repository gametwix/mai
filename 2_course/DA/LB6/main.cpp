#include <iostream>
#include "bignum.hpp"



int main(){
    NBigNum::TBigNum num[3];
    num[0] = "123456"_bn;
    std::cin >> num[1] >> num[2];
    std::cout << num[0] << "\t" << num[1] << "\t"<< num[2]  << std::endl;
    num[2] = num[2] * num[1];
    std::cout << num[0] << "\t" << num[1] << "\t"<< num[2]  << std::endl;
    return 0;
    
}