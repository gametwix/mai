#include "vector.hpp"
#include <iostream>

class Dd
{
    public:
    int a;
    void operator =(int b)
    {
        a+=b;
    }
    void operator =(Dd b)
    {
        this->a+=b.a;
    }
    Dd()
    {
        std::cout << "i alive" << std::endl;
        a = 3;
    }
};


int main()
{
    NVector::TVector<int> a;
    for(int i = 0; i < a.End();++i)
    {
        std::cout<< a[i] << std::endl;
    }
}