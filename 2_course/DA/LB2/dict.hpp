#pragma once

#include "pair.hpp"
#include "string.hpp"
#include "rb_vect.hpp"

#include <iostream>
#include <cstring>

void parse_comand(NString::TString str)
{
    if(str[0] == '+')
    {
        int word_end = str.find(' ',2);
        NString::TString word;
        NString::TString num;
        std::memcpy(word.str,&str.str[2],word_end-2);
        word.size = word_end-2;
        std::memcpy(num.str,&str.str[word_end+1],str.size - (word_end+2));
        num.size = str.size - (word_end+2);


    }
}
