#pragma once
#include "string.hpp"

namespace NPair
{
    class TPair
    {
        public:
            unsigned long long Num;
            NString::TString Str;

            TPair(NString::TString rStr,unsigned long long rNum)
            {
                Str = rStr;
                Num = rNum;
            }

            bool operator==(const TPair& second)
            {
                return (Str == second.Str);
            }

            bool operator<(const TPair& second)
            {
                return (Str < second.Str);
            }

            void operator=(const TPair& second)
            {
                Num = second.Num;
                Str = second.Str;
            }
    };
}//namespace NPair