#include "vector.hpp"
#include "carnum.hpp"
#include <iostream>


class TBase_elem
{
    public:
    NCarnum::TCarnum Carnum;
    char Str[64];

    TBase_elem()
    {
        for(int i = 0; i<64;i++)
        {
            Str[i] = '\0';
        }
    }

    friend std::istream& operator>>(std::istream &in, TBase_elem &elem)
        {
            in >> elem.Carnum;
            in.peek();
            in >> elem.Str;
            return in;
        }

    friend std::ostream& operator<< (std::ostream &out, const TBase_elem &elem)
        {
            out << elem.Carnum << "\t" <<  elem.Str;
            return out;
        }
};



int main()
{
    TBase_elem elem;
    std::cin >> elem;
    std::cout << elem << std::endl;
}