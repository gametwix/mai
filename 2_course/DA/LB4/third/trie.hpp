#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>


class TTrie{
    class TNode{
    public:
        bool Last;
        long long Sym;
        std::vector<int> Jockers;
        TNode* Parent;
        TNode* Suffix;
        TNode* SubLast;
        std::unordered_map<long long,TNode*> Childs;

        TNode(long long inSym = -1,bool inLast = false):Sym(inSym),Last(inLast){
        Parent = nullptr;
        Suffix = nullptr;
        SubLast = nullptr;
        }   
    };

    TNode* Root;
    TNode* Cur;

public:
};