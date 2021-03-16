#include "bignum.hpp"
#include <string>


namespace NBigNum{
TBigNum::TBigNum():Size(0), MaxSize(0){}
TBigNum::TBigNum(long long size): Size(0),MaxSize(size){
    Nums.resize(size);
}
TBigNum::TBigNum(const TBigNum &other):Size(other.Size), MaxSize(other.MaxSize){
    Nums.resize(other.MaxSize);
    std::copy(other.Nums.begin(),other.Nums.begin()+other.Size,Nums.begin());
}

TBigNum::TBigNum(const char* &str){
    (*this).FromStr(str);
}

TBigNum::~TBigNum(){}

long long TBigNum::GetSize(){ return Size; }
long long TBigNum::GetMaxSize(){ return MaxSize; }
int TBigNum::GetNum(long long pos){ return Nums[pos]; }
void TBigNum::SetSize(long long size){ Size = size; }
void TBigNum::SetMaxSize(long long maxsize){ MaxSize = maxsize; }
void TBigNum::SetNum(long long pos,int num){ Nums[pos] = num; }

void TBigNum::Revers(){
    int tmp;
    for(long long i = 0;i < Size/2 ;++i){
        tmp = Nums[Size - i - 1];
        Nums[Size - i - 1] = Nums[i];
        Nums[i] = tmp;
    }
}

TBigNum& TBigNum::operator=(const TBigNum other){
    if(&other == this) return *this;
    if(MaxSize < other.Size){
        Nums.resize(other.Size);
        MaxSize = other.Size;
    }
    Size = other.Size;
    std::copy(other.Nums.begin(),other.Nums.begin()+other.Size,Nums.begin());
    return *this;
}

TBigNum& TBigNum::operator=(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
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
    long long size = str.size();
    //std::cout << size <<std::endl;
    long long size_num = size / POW + ((size % POW > 0 ) ? 1:0);
    
    long long start = 0;
    long long length = 0;
    //std::cout << size_num <<std::endl;
    if(MaxSize < size_num){
        MaxSize = size_num;
        Nums.resize(MaxSize);
    }
    
    
    for( long long i = 0; i < size_num;++i){
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

    int i = size_num - 1;
    while( i > 0 && Nums[i] == 0) --i;
    Size = i+1;
}

TBigNum TBigNum::ShortDiv(TBigNum other){
    if(other.Size == 1 && other.Nums[0] == 0){ throw -1; }
    if(Size == 1 && other.Size == 1){ 
        TBigNum ans;
        ans.FromStr(std::to_string(Nums[0]/other.Nums[0]));
        return ans;
    }
    TBigNum tmp = *this;
    TBigNum ans(0);
    for(int i = Size - 1; i >=0; --i){
        int q = Nums[i] / other.Nums[0];
        TBigNum mul = other*q;
        tmp = tmp.ShiftMinus(mul,i);
        ans.Nums.insert(ans.Nums.begin(),q);
        ++ans.MaxSize;
        ++ans.Size;
    }

    long long i = ans.Size - 1;
    while((i > 0) && (ans.Nums[i] == 0)) --i;
    ans.Size = i+1;
    return ans;
}

TBigNum TBigNum::LongDiv(TBigNum other){
    if(other.Size == 1 && other.Nums[0] == 0){ throw -1; }
    if(Size < other.Size){
        TBigNum ans;
        ans.FromStr("0");
        return  ans; }
    if(Size == 1 && other.Size == 1){ 
        TBigNum ans;
        ans.FromStr(std::to_string(Nums[0]/other.Nums[0]));
        return ans;
    }
    long long n = other.Size;
    long long m = Size - other.Size;
    TBigNum tmp(Size + 1);
    TBigNum ans(0);
    tmp = *this;
    int norm = BASE/(other.Nums[n - 1] + 1);
    tmp = tmp * norm;
    other = other * norm;

    std::cout << tmp << " " << other  << std::endl;
    for(int i = m; i >= 0; --i){
        std::cout << i  << std::endl;
        int q = (tmp.Nums[i+n]*BASE + tmp.Nums[i+n-1]) / other.Nums[n-1];
        int r = (tmp.Nums[i+n]*BASE + tmp.Nums[i+n-1]) % other.Nums[n-1];
        while(r < BASE){
            if(q == BASE || q*other.Nums[n-2] > BASE * r + tmp.Nums[i+n-2]){
                std::cout << other.Nums[n-2]  << std::endl;
                --q;
                r += other.Nums[n-1];
            } else break;
        }
        try {
            TBigNum mul = other*q;
            tmp = tmp.ShiftMinus(mul,i);
        }
        catch(int i){
            --q;
            TBigNum mul = other*q;
            tmp = tmp.ShiftMinus(mul,i);
        }
        ans.Nums.insert(ans.Nums.begin(),q);
        ++ans.MaxSize;
        ++ans.Size;
    }
    long long i = ans.Size - 1;
    while((i > 0) && (ans.Nums[i] == 0)) --i;
    ans.Size = i+1;
    return ans;
}

TBigNum TBigNum::operator+(TBigNum& other){
    int past = 0;
    int tmp = 0;
    if(other.Size > Size)
        return other + (*this);
    TBigNum answer(Size + 1);
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] + other.Nums[i] + past;
        past = 0;
        if (tmp >= BASE){
            tmp = tmp - BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(long long i = other.Size; i < Size; ++i){
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
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] - other.Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(long long i = other.Size; i < Size; ++i){
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
    
    long long i = Size - 1;
    while((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;

    return answer;
}

TBigNum TBigNum::operator-(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    int past = 0;
    int tmp = 0;
    if(other.Size > Size){
        throw -1;
    }
    TBigNum answer(Size);
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i] - other.Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i] = tmp;
    }

    for(long long i = other.Size; i < Size; ++i){
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
    
    long long i = Size - 1;
    while((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;

    return answer;
}


TBigNum TBigNum::operator*(TBigNum& other){
    int tmp = 0;
    int past = 0;
    TBigNum answer(Size + other.Size+1);

    for(long long i = 0; i < Size; ++i){
        for(long long j = 0;j < other.Size;++ j){
            tmp = Nums[i]*other.Nums[j] + answer.Nums[i+j] + past;
            past = tmp / BASE;
            tmp = tmp % BASE;
            answer.Nums[i+j] = tmp;
        }
        answer.Nums[i + other.Size] = past;
        past = 0;
    }

    long long i = Size + other.Size - 1;
    
    while ((i > 0) && (answer.Nums[i] == 0)) --i;

    answer.Size = i+1;

    return answer;
}


TBigNum TBigNum::operator*(int other){
    if(other > BASE){
        TBigNum tmp;
        tmp.FromStr(std::to_string(other));
        return (*this) * tmp;
    }
    int tmp = 0;
    int past = 0;
    TBigNum answer(Size + 1);

    for(long long i = 0; i < Size; ++i){
        tmp = Nums[i]*other + past;
        past = tmp / BASE;
        tmp = tmp % BASE;
        answer.Nums[i] = tmp;
    }
    answer.Nums[Size] = past;

    long long i = Size;
    while ((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;
    //std::cout << "ans\t" << answer << std::endl;
    return answer;
}

TBigNum TBigNum::ShiftMinus(TBigNum& other,int shift){
    int past = 0;
    int tmp = 0;
    if(other.Size > Size-shift){
        throw -1;
    }
    TBigNum answer(Size+shift);
    answer = *this;
    for(long long i = 0; i < other.Size; ++i){
        tmp = Nums[i+shift] - other.Nums[i] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i+shift] = tmp;
    }

    for(long long i = other.Size; i < Size && i+shift < MaxSize; ++i){
        tmp = Nums[i+shift] - past;
        past = 0;
        if (tmp < 0){
            tmp = tmp + BASE;
            past = 1;
        }
        answer.Nums[i+shift] = tmp;
    }

    if(past > 0)
        throw -1;
    
    long long i = Size - 1;
    while((i > 0) && (answer.Nums[i] == 0)) --i;
    answer.Size = i+1;

    return answer;
}

TBigNum TBigNum::operator/(TBigNum other){
    if(other.Size == 1 && other < BASE)
        return this->ShortDiv(other);
    else
        return this->LongDiv(other);
}

TBigNum TBigNum::operator/(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    if(other.Size == 1 && other < BASE)
        return this->ShortDiv(other);
    else
        return this->LongDiv(other);
}

TBigNum TBigNum::operator^(TBigNum other){
    TBigNum ans;
    std::cout << other <<std::endl;
    if(other == 0){
        if(*this == 0)
            throw -1;
        else{
            ans.FromStr("1");
            return ans;
        }
    }
    if(other == 1)
        return *this;
    else{
        if(other.Nums[0] % 2 == 0){
            TBigNum tmp = (*this ^ (other / 2));
            std::cout << tmp << std::endl;
            return tmp*tmp;
        } else
            return ((*this) ^ (other - 1));
    }
}

bool TBigNum::operator<(const TBigNum& other){
    if(Size < other.Size) return true;
    else if(Size > other.Size) return false;
    else {
        bool ans = false;
        for(long long i = 0; i < Size; ++i){
            if(Nums[i] < other.Nums[i]) ans = true;
        }
        return ans;
    }
}

bool TBigNum::operator>(const TBigNum& other){
    if(Size > other.Size) return true;
    else if(Size < other.Size) return false;
    else{
        bool ans = false;
        for(int i = Size; i > 0; --i)
            if(Nums[Size - 1] > other.Nums[Size - 1]) ans = true;
        return ans;
    }
}

bool TBigNum::operator==(const TBigNum& other){
    if(Size != other.Size) return false;
    else{
        bool ans = true;
        for(int i = Size; i > 0; --i)
            if(Nums[Size - 1] != other.Nums[Size - 1]) ans = false;
        return ans;
    }
}

bool TBigNum::operator<(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    if(Size < other.Size) return true;
    else if(Size > other.Size) return false;
    else {
        bool ans = false;
        for(long long i = 0; i < Size; ++i){
            if(Nums[i] < other.Nums[i]) ans = true;
        }
        return ans;
    }
}

bool TBigNum::operator>(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    if(Size > other.Size) return true;
    else if(Size < other.Size) return false;
    else{
        bool ans = false;
        for(int i = Size; i > 0; --i)
            if(Nums[Size - 1] > other.Nums[Size - 1]) ans = true;
        return ans;
    }
}

bool TBigNum::operator==(int number){
    TBigNum other;
    other.FromStr(std::to_string(number));
    if(Size != other.Size) return false;
    else{
        bool ans = true;
        for(int i = Size; i > 0; --i)
            if(Nums[Size - 1] != other.Nums[Size - 1]) ans = false;
        return ans;
    }
}

} //namespace BigNum



