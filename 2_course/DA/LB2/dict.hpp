#pragma once

#include "pair.hpp"
#include "string.hpp"
#include "rb_vect.hpp"

#include <iostream>
#include <cstring>

void parse_comand(NString::TString &cmd)
{
    NString::TString word;
    NString::TString path;
    int num;
    switch(cmd[0])
    {
        case '+':
        std::cin >> word >> num;
        std::cout << word << '|' << num << std::endl;
        break;
        case '-':
        std::cin >> word >> num;
        std::cout << word << '|' << num << std::endl;
        break;
        case '!':
        std::cin >> word >> path;
        if(word == "Load")
        {

        }
        else
        {
            
        }
        break;
        default:
        std::cin >> word ;
        std::cout << word << std::endl;
        break;

    }
    
}
