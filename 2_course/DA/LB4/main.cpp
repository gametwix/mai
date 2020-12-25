#include <iostream>
#include <vector>
#include "ahok.hpp"

size_t CreateBor(TAhoKarasik &ahk)
{
    struct SPattern{
        std::vector<long long> Pattern;
        size_t Pos_start;
    };

    size_t pos = 0;
    long long num = 0;
    size_t pattern_count = 0;
    size_t ch = std::getchar();
    bool in_num = false;
    bool in_pat = false;
    std::vector<SPattern*> patterns;
    SPattern* cur_pattern = new SPattern();

    while(true){
        if(ch == 63){
            pos++;
            patterns.push_back(cur_pattern);
            cur_pattern = new SPattern();
            in_pat = false;
        }
        else if((ch>47)&&(ch<58)){
            num *= 10;
            num += ch-48;
            in_num = true;
            
        }
        else if(ch == 32 && in_num){
            in_num = false;
            if(!in_pat)
            {
                cur_pattern->Pos_start = pos;
                in_pat = true;
            }
            cur_pattern->Pattern.push_back(num);
            num = 0;
            ++pos;
        }
        ch = std::getchar();
        if(ch == 10){
            if(!in_pat)
                cur_pattern->Pos_start = pos;
            cur_pattern->Pattern.push_back(num);
            patterns.push_back(cur_pattern);
            break;
        }
    }    
    for(auto i:patterns){
        ahk.Push(i->Pattern,i->Pos_start);
        ++pattern_count;
        delete(i);
    }
    ahk.SearchSufPtr();
    return pattern_count;
}

void ReadText(std::vector<long long> &text,std::vector<size_t> &size_line){
    char ch;
    long long num = 0;
    size_t num_word = 0;
    bool in_num = false;
    while(std::cin.get(ch)){
        int in = ch;
        if((in>47)&&(in<58)){
            num *= 10;
            num += in-48;
            in_num = true;
        }
        else if(in == 32 && in_num){
            in_num = false;
            text.push_back(num);
            num = 0;
            ++num_word;
        }
        else if(in == 10){
            if(in_num){
                in_num = false;
                text.push_back(num);
                num = 0;
                ++num_word;
            }
            size_line.push_back(num_word-1);
        }
    }
    if(in_num){
                in_num = false;
                text.push_back(num);
                num = 0;
                ++num_word;
            }
            size_line.push_back(num_word-1);
}


int main()
{
    size_t pattern_count;
    TAhoKarasik ahk;
    pattern_count = CreateBor(ahk);
    std::vector<long long> text;
    std::vector<size_t> size_line;
    ReadText(text,size_line);
    std::vector<size_t> pos;
    pos.resize(text.size());
    ahk.Find(text,pos);
    size_t size_text = pos.size();
    for(size_t i = 0;i < size_text;++i)
    {
        if(pos[i]==pattern_count)
        {
            if(i>=size_line[size_line.size()-1])
            {
                std::cout<< "("<<size_line.size()<<","<< i - size_line[size_line.size()-1] +1 <<")" <<std::endl;
            }
            else{
                for(int j = 0; j<size_line.size()-1;++j)
                {
                    if(i>=size_line[j] && i<=size_line[j])
                    {
                        std::cout<< "("<<j+1<<","<< i - size_line[j] +1 <<")" <<std::endl;
                    }
                }
            }
        }
    }
    return 0;	
}