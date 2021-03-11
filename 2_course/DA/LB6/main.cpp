#include <iostream>
#include "bignum.hpp"



int main(){
    NBigNum::TBigNum num[2];
    char sym;
    while(std::cin >> num[0] >> num[1] >> sym){
        if(sym == '+')
            std::cout << num[0] + num[1] << std::endl;
        if(sym == '-'){
            try{
                std::cout << num[0] - num[1] << std::endl;
            } catch( int i){
                std::cout << "Error" <<std::endl;
            }
        }
            
        if(sym == '*')
            std::cout << num[0] * num[1] << std::endl;
}
    return 0;
    
}