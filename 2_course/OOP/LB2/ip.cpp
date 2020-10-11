#include "ip.hpp"

//Конструкторы

NIP::IPAddress::IPAddress()
{
    for(int i = 0;i < 4;++i)
    {
        bites[i]=0;
    }
}

NIP::IPAddress::IPAddress(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4) 
{
    bites[0] = b1;
    bites[1] = b2;
    bites[2] = b3;
    bites[3] = b4;
}

NIP::IPAddress::IPAddress(const NIP::IPAddress::IPAddress& b)
{
    bites[0] = b.bites[0];
    bites[1] = b.bites[1];
    bites[2] = b.bites[2];
    bites[3] = b.bites[3];
}


//Оператор присваивания
void NIP::IPAddress::operator =(const NIP::IPAddress::IPAddress& b)
{
    bites[0] = b.bites[0];
    bites[1] = b.bites[1];
    bites[2] = b.bites[2];
    bites[3] = b.bites[3];
}

//Оператор возврата битов
unsigned char& NIP::IPAddress::operator [](int i)
{
    return bites[i];
}

