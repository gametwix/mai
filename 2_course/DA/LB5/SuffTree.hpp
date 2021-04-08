#pragma once

#include <memory>
#include <unordered_map>
#include <string>

class TSuffTree{
private:
    const char TermSym = '$';
    class TNode;
    TNode Root;
    std::shared_ptr<TNode> LastCreate;
    std::string text; 
    int End;
public:
    TSuffTree(const std::string& inp_text);
    int Search(std::string pattern);
    void Initialize(const std::string& inp_text);
    void ExternTree(int len);
};


class TSuffTree::TNode{
    private:
        std::unordered_map<char,std::shared_ptr<TNode>> Children;   //Таблица детей
        int Start;                                                  //Номер налача участка текста
        std::shared_ptr<int> End;                                   //Указатель на номер конца участка текста
        std::shared_ptr<TNode> SuffixLink;                          //Суффиксная ссылка
        int SuffixIndex;                                            //Номер листа (если не лист равен -1)
    public:
        //Конструктор для промежуточного узла
        TNode(int start, int* end,TNode *sufflink): Start(start),
                                                    End(std::shared_ptr<int>(end)),
                                                    SuffixIndex(-1),
                                                    SuffixLink(std::shared_ptr<TNode>(sufflink)){}
        //Конструктор для листа
        TNode(int start, int* end,int suffind): Start(start),
                                                End(std::shared_ptr<int>(end)),
                                                SuffixIndex(suffind),
                                                SuffixLink(nullptr){}
};
