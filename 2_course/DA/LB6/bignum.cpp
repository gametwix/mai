#include "bignum.hpp"


namespace NBigNum{
TBigNum::TBigNum():Size(0), MaxSize(0){}
TBigNum::TBigNum(unsigned long long size): Size(0),MaxSize(size){
    Nums.resize(size);
}
TBigNum::TBigNum(const TBigNum &other):Size(other.Size), MaxSize(other.MaxSize){
    Nums.resize(other.MaxSize);
    std::copy(other.Nums.begin(),other.Nums.begin()+other.Size,Nums.begin());
}

TBigNum::~TBigNum(){}

unsigned long long TBigNum::GetSize(){ return Size; }
unsigned long long TBigNum::GetMaxSize(){ return MaxSize; }
int TBigNum::GetNum(unsigned long long pos){ return Nums[pos]; }
void TBigNum::SetSize(unsigned long long size){ Size = size; }
void TBigNum::SetMaxSize(unsigned long long maxsize){ MaxSize = maxsize; }
void TBigNum::SetNum(unsigned long long pos,int num){ Nums[pos] = num; }

TBigNum& TBigNum::operator=(const TBigNum& other){
    if(&other == this) return *this;
    if(MaxSize < other.Size){
        Nums.resize(other.Size);
        MaxSize = other.Size;
    }
    Size = other.Size;
    std::copy(other.Nums.begin(),other.Nums.begin()+other.Size,Nums.begin());
    return *this;
}

void TBigNum::FromStr(std::string str){
    unsigned long long size = str.size();
    //std::cout << size <<std::endl;
    unsigned long long size_num = size / POW + ((size % POW > 0 ) ? 1:0);
    
    unsigned long long start = 0;
    unsigned long long length = 0;
    //std::cout << size_num <<std::endl;
    if(MaxSize < size_num){
        MaxSize = size_num;
        Nums.resize(MaxSize);
    }
    Size = size_num;
    
    for( unsigned long long i = 0; i < size_num;++i){
        start = size - i*POW;
        if(start >= POW){
            length = POW;
            start -= POW;
        } else {
            length = start;
            start = 0;
        }
        //std::cout << stoi(str.substr(start,length)) <<std::endl;
        Nums[i]=stoi(str.substr(start,length));
    }   
}

TBigNum TBigNum::operator+(TBigNum& other){
    int past = 0;
    int tmp = 0;
    if(other.Size > Size)
        return other + (*this);
    TBigNum answer(Size + 1);
    for(unsigned long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] + other.Nums[i] + past;
        past = 0;
        if (tmp >= BASE){
            tmp = tmp - BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(unsigned long long i = other.Size; i < Size; ++i){
        tmp = Nums[i] + past;
        past = 0;
        if (tmp >= BASE){
            tmp = tmp - BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }
    answer.Size = Size;

    if(past > 0){
        answer.Nums[Size] = past;
        ++answer.Size;
    }
    return answer;
}


TBigNum TBigNum::operator-(TBigNum& other){
    int past = 0;
    int tmp = 0;
    if(other.Size > Size){
        throw -1;
    }
    TBigNum answer(Size);
    for(unsigned long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] - other.Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(unsigned long long i = other.Size; i < Size; ++i){
        tmp = Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    if(past > 0)
        throw -1;
    
    unsigned long long i = Size - 1;
    while((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;

    return answer;
}

TBigNum TBigNum::operator*(TBigNum& other){
    int tmp = 0;
    int past = 0;
    TBigNum answer(Size + other.Size);

    for(unsigned long long i = 0; i < Size; ++i){
        for(unsigned long long j = 0;j < other.Size;++ j){
            tmp = Nums[i]*other.Nums[j] + answer.Nums[i+j] + past;
            past = tmp / BASE;
            tmp = tmp % BASE;
            answer.Nums[i+j] = tmp;
        }
        answer.Nums[i + other.Size] = past;
    }

    unsigned long long i = Size + other.Size - 1;
    std::cout << i << std::endl;
    while ((i > 0) && (answer.Nums[i] == 0)){
        std::cout << "Num " << (answer.Nums[i] == 0) << std::endl;
        --i;
    } 
    std::cout << i << std::endl;
    answer.Size = i+1;

    return answer;
}


} //namespace BigNum



