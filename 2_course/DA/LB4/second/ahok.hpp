#pragma once

#include <vector>
#include <unordered_map>
#include <queue>

class TAhoKorasik{
protected:
class TNode{
    public:
    using node_ptr = TNode*;
    long long Sym;                 //Data
    bool Last;
    std::vector<size_t> Jockers;
    node_ptr Parent;               //Ptrs
    node_ptr Suffix;
    node_ptr SubLast;
    std::unordered_map<long long,node_ptr> Childs;

    TNode(long long inSym = -1,bool inLast = false):Sym(inSym),Last(inLast){
        Parent = nullptr;
        Suffix = nullptr;
        SubLast = nullptr;
    }

    ~TNode(){
        for(auto Child: Childs){
            delete(Child.second);
        }
    }

    node_ptr ChildPrt(long long inSym){
        try{
            return Childs.at(inSym);
        }
        catch(std::out_of_range){
            return 0;
        }
    }
};//TNode
using node_ptr = TNode::node_ptr;

node_ptr Root;

TAhoKorasik():Root(new TNode()){}
~TAhoKorasik(){
    delete(Root);
}

void Push(const std::vector<long long> &pattern, size_t pos){
    node_ptr cur = Root;
    for(auto elem_pattern: pattern){
        node_ptr child = cur->ChildPrt(elem_pattern);
        if(child == nullptr){
            child = new TNode(elem_pattern);
            child->Parent = cur;
            cur->Childs.insert({elem_pattern,child});
        }
        cur = child;
    }
    cur->Last = true;
    cur->Jockers.push_back(pos);
}

void BorSuf(){
    //BFS
    std::queue<node_ptr> queue;
    queue.push(Root);
    while(!queue.empty()){
        node_ptr elem = queue.front();
        queue.pop();
        for(auto child: elem->Childs)
        {
            queue.push(child.second);
        }
        //~BFS
        //Suf
        if(elem == Root) //not for Root
		    continue;
        
        node_ptr parent = elem->Parent;
        parent = parent->Suffix;
        while(parent != nullptr && parent->ChildPrt(elem->Sym) == nullptr)
            parent = parent->Suffix;
        
        if(parent == nullptr)
            elem->Suffix = Root;
        else
            elem->Suffix = parent->ChildPrt(elem->Sym);
        //~Suf
        //SubLast
        if(elem->Suffix->Last)
            elem->SubLast = elem->Suffix;
        else if(elem->Suffix->SubLast != nullptr)
            elem->SubLast = elem->Suffix->SubLast;
        //~SubLast
    }//while
}

};//TAhoKorasik