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

    void operator=(TBase_elem &second_elem)
    {
        this->Carnum = second_elem.Carnum;
        for(int i=0;i<64;++i)
        {
            this->Str[i] = second_elem.Str[i];
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

NVector::TVector<TBase_elem> Sort_ch(NVector::TVector<TBase_elem> &base, int num)
{
    int k[26] = {};
    NVector::TVector<TBase_elem> newbase;

    for(int i = 0;i < base.End();++i)
    {
        ++k[(int)base[i].Carnum.Sym[num]-65];
    }
    for(int i=1;i<26;++i)
    {
        k[i]+=k[i-1];
    }
    for(int i = base.End() - 1;i >= 0;--i)
    {
        newbase[k[(int)base[i].Carnum.Sym[num]-65]] = base[i];
    }
    return newbase;
}

void Sort(NVector::TVector<TBase_elem> &base)
{
    base = Sort_ch(base,0);
}

int main()
{
    TBase_elem elem;
    NVector::TVector<TBase_elem> base;
    while(std::cin >> elem)
    {
        //std::cout << elem << std::endl;
        base.Push_back(elem);
    }

    Sort(base);
    std::cout << "1" << base.End()<<base[0]<< std::endl;
    for(int i = 0; i < base.End(); ++i)
    {
        std::cout << base[i] << std::endl;
    }

   
}