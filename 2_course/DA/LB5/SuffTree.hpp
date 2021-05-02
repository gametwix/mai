#pragma once
//Test algorihm O^3


#include <memory>
#include <unordered_map>
#include <string>

struct TNode{
        std::unordered_map<char,std::shared_ptr<TNode>> Children;   //Таблица детей
        int Start;                                                  //Номер налача участка текста
        std::shared_ptr<int> End;                                   //Указатель на номер конца участка текста
        std::shared_ptr<TNode> SuffixLink;                          //Суффиксная ссылка
        int SuffixIndex;                                            //Номер листа (если не лист равен -1)
        //Конструктор для промежуточного узла
        TNode(int start, int avanp):Start(start),
                                    SuffixIndex(-1)
                                    {
                                        End = std::shared_ptr<int>(new int(avanp));
                                    }
        //Конструктор для листа
        TNode(int start, int* end,int suffind): Start(start),
                                                End(std::shared_ptr<int>(end)),
                                                SuffixIndex(suffind),
                                                SuffixLink(nullptr){}
};

class TSuffTree{
private:
    const char TermSym = '$';
    int End = 0;
    TNode Root;
    std::shared_ptr<TNode> LastCreate;
    std::string Text; 
    int NumLits = 0;
public:
    TSuffTree(const std::string& inp_text);
    int Search(std::string pattern);
    void Initialize(const std::string& inp_text);
    void ExternTree(int len);
};


void TSuffTree::Initialize(const std::string& inp_text){
    Text = inp_text;                //Копируем текст
    int size = Text.length();       //Считываем длину текств
    for(int i = 0;i < size;++i){    //Добавляем все суффексы для пефикса заданной длины
        ExternTree(i);
    }
}

void TSuffTree::ExternTree(int len){
    //увеличиваем для всех листьев точку конца
    End++;
    //Создаем переменные с последней пройденной нодой и относительной позцией
    int pos = 0;
    std::shared_ptr<TNode> last_node(&Root);
    //Добавляем букву для всех оставшихся суффиксов
    for(int i = NumLits; i < len; i++){
        pos = last_node->Start;
        int j = 0;
        while(pos != len-1){
            if(Text[pos+1] == Text[last_node->Start + j]){
                pos++;
            } else {
                break;
            }
            if(pos == last_node->End*){

            }
        }
    }
}


