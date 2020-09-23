
#include <iostream>
#include "britishmoney.hpp"

int main()
{

    BritishMoney a;
    BritishMoney b;
    a.pounds = 10;
    a.shilling = 13;
    a.penny = 7;
    b = a*1.6;
    a.print();
    b.print();
    b = b/1.6;
    b.print();
    return 0;
}