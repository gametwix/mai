#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

#define BASE 100000
#define POW 5

namespace NBigNum{
class TBigNum{
private:
    unsigned long long Size,MaxSize;
    std::vector<unsigned int> Nums;

public:
    
    TBigNum();
    TBigNum(unsigned long long size);
    TBigNum(const TBigNum &other);
    ~TBigNum();

    unsigned long long GetSize();
    unsigned long long GetMaxSize();
    int GetNum(unsigned long long pos);
    void SetSize(unsigned long long size);
    void SetMaxSize(unsigned long long maxsize);
    void SetNum(unsigned long long pos,int num);
    void FromStr(std::string str);
    void Revers();
    
    TBigNum& operator=(const TBigNum& other);
    TBigNum operator+(TBigNum& other);
    TBigNum operator-(TBigNum& other);
    TBigNum operator*(TBigNum& other);
    TBigNum operator*(int other);
    TBigNum operator/(TBigNum& other);


    friend std::ostream& operator<< (std::ostream &out, const TBigNum &num){
        unsigned long long size = num.Size;
        for(unsigned long long i = size; i > 0 ; --i){
            out << num.Nums[i-1];
        }
        return out;
    }

    friend std::istream& operator>> (std::istream& in,TBigNum& num){
        std::string str;
        in >> str;
        num.FromStr(str);
        return in;
    }

    
};


}//namespace BigNum

inline NBigNum::TBigNum operator "" _bn(const char* str, size_t size){
    NBigNum::TBigNum tmp;
    tmp.FromStr(str);
    return tmp;
}