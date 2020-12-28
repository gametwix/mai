#include "ahok.hpp"
#include <iostream>
#include <vector>

int ReadPattern(TAhoKorasik &ahok){
    char ch;
    int ind;
    int pos_pattern = 0;
    bool innum = false;
    long long num = 0;
    int num_pattern = 0;
    std::vector<long long> pattern;
    while(std::cin.get(ch)){
        ind = ch;
        if(ind > 47 && ind < 58){
            innum = true;
            num *= 10;
            num += ind - 48;
        }
        if(ind == 32 && innum){
            ++pos_pattern;
            pattern.push_back(num);
            num = 0;
            innum = false;
        }
        if(ind == 63){
            ahok.Push(pattern,pos_pattern-1);
            ++num_pattern;
            pattern.clear();
            ++pos_pattern;
        }
        if(ind == 10){
            if(innum){
                ++pos_pattern;
                pattern.push_back(num);
                num = 0;
                innum = false;
            }
            ahok.Push(pattern,pos_pattern-1);
            ++num_pattern;
            break;
        }
    }
    return num_pattern;
}


void ReadText(std::vector<long long> &text,std::vector<int> &poslast)
{
    char ch;
    int ind;
    int numelem = 0;
    long long num = 0;
    bool innum = false;
    while(std::cin.get(ch)){
        ind = ch;
        if(ind > 47 && ind < 58){
            innum = true;
            num *= 10;
            num += ind - 48;
        }
        if(ind == 32 && innum){
            innum = false;
            text.push_back(num);
            ++numelem;
            num = 0;
        }
        if(ind == 10){
            if(innum)
            {
                innum = false;
                text.push_back(num);
                ++numelem;
                num = 0;
            }
            poslast.push_back(numelem-1);
        }
    }
    if(innum)
    {
        ++numelem;
        text.push_back(num);
        poslast.push_back(numelem-1);
    }
}

int main(){
    TAhoKorasik ahok;
    int num_pattern;
    std::vector<long long> text;
    std::vector<int> lastposline;
    num_pattern = ReadPattern(ahok);
    ReadText(text,lastposline);
    int intext = text.size();
    std::vector<int> pos(intext);
    ahok.BorSuf();
    ahok.Find(text,pos);
    int size_lines = lastposline.size();
    for(int i = 0; i < intext; ++i){
        if(pos[i] == num_pattern){
            if(i > lastposline[size_lines - 1]){
                std::cout << size_lines<<", "<< i - lastposline[size_lines - 1] <<std::endl;
                continue;
            }
            if(i <= lastposline[0]){
                std::cout << 1 << ", "<< i+1 <<std::endl;
                continue;
            }
            for(int j = 0; j < size_lines - 1; ++j){
                if(i > lastposline[j] && i <= lastposline[j+1])
                {
                    std::cout << j+2 << ", " << i - lastposline[j] <<std::endl;
                    break;
                }
            }
        }
    }

    return 0;
}