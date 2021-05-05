#include "SuffTree.hpp"
#include <iostream>

void TSuffTree::Init(std::string InpText){
    Text = InpText + "$";
    int SizeText = Text.size();
    for(int i = 0;i < SizeText; ++i){
        AddAllSuffix(i);
        Print();
    }
}

void TSuffTree::AddAllSuffix(int InpEnd){
    std::cout << "AddAllSuffix\t" << InpEnd << std::endl;
    //Добавляем ко всем листьям символ
    ++(*End);
    
    std::shared_ptr<TNode> cur_node(Root);
    std::shared_ptr<TNode> last_add(nullptr);
    std::shared_ptr<TNode> new_node(nullptr);
    int cur_pos_in_node = 0;

    std::cout << "Cur_node before: " << cur_node << std::endl;
    GoTo(cur_node, cur_pos_in_node, ListNum, InpEnd - 1);
    std::cout << "Cur_node after: " << cur_node << std::endl;
    if(!CreateNode(cur_node,last_add,cur_pos_in_node,InpEnd))
        return;
    else{
        if(last_add->ListId != -1){
            cur_node = cur_node->SuffixLink;
            if(cur_node == Root)
                --cur_pos_in_node;                                                  //сюда по идее не должно зайти
        } else {
            char Save_point;
            if(cur_node->Parent == Root)
                Save_point = Text[cur_node->Start + 1];
            else
                Save_point = Text[cur_node->Start];
            cur_node = cur_node->
        }
    }
    
    std::cout << ListNum << "\t" << InpEnd << std::endl;
    for(int i = ListNum; i <= InpEnd;++i){                                         //Все суффиксы
        if(CreateNode(cur_node,new_node,cur_pos_in_node,InpEnd)){
            if(last_add->ListId != -1){
                last_add->SuffixLink = new_node;
                last_add = new_node;
            }
            cur_node = cur_node->SuffixLink;
        } else {
            break;
        }
    }
}

void TSuffTree::GoTo(std::shared_ptr<TNode> &CurNode, int &pos, int Start, int Finish){
    for(int i = Start; i <= Finish; ++i){
        if(CurNode == Root){
            if(CurNode->Children.find(Text[i]) != CurNode->Children.end()){
                CurNode = CurNode->Children.find(Text[i])->second;
                pos = 1;
            } else {
                throw -1;
            }
        } else {
            if(CurNode->Start + pos > *(CurNode->End)){
                if(CurNode->Children.find(Text[i]) != CurNode->Children.end()){
                    CurNode = CurNode->Children.find(Text[i])->second;
                    pos = 1;
                } else {
                    throw -1;
                }
            }else{
                if(Text[CurNode->Start + pos] == Text[i]){
                    pos++;
                }else{
                    throw -1;
                }
            }
        }
    }
}

bool TSuffTree::CreateNode(std::shared_ptr<TNode> &Node, std::shared_ptr<TNode> &NewNode,int pos, int AddNum){
    std::cout << "Create: Root: " << Root << "Node: " << Node << std::endl;
    if(Node == Root){                                                               //если в корне
        if(Node->Children.find(Text[AddNum]) != Node->Children.end()){
            return false;
        } else {
            NewNode = std::shared_ptr<TNode>(new TNode(AddNum,End,ListNum + 1));
            ListNum++;
            Node->Children.insert({Text[AddNum],NewNode});
            NewNode->Parent = Node;
            return true;
        }
    } else {
        if(Node->Start + pos > *(Node->End)){                                         //если в конце ноды
            if(Node->Children.find(Text[AddNum]) != Node->Children.end()){
                return false;
            } else {
                NewNode = std::shared_ptr<TNode>(new TNode(AddNum,End,ListNum + 1));
                ListNum++;
                Node->Children.insert({Text[AddNum],NewNode});
                NewNode->Parent = Node;
                return true;
            }
        } else {                                                                    //если посреди ноды
            if(Text[Node->Start+pos] == Text[AddNum]){
                return false;
            } else {
                NewNode = std::shared_ptr<TNode>(new TNode(Node->Start + pos,Node->End,Node->ListId));
                Node->End = std::shared_ptr<int>(new int(Node->Start + pos - 1));
                NewNode->Children = Node->Children;
                NewNode->Parent = Node;
                Node->Children.insert({Text[Node->Start + pos],NewNode});
                std::shared_ptr<TNode> List(new TNode(AddNum,End,ListNum));
                ListNum++;
                Node->Children.insert({Text[AddNum],List});
                List->Parent = Node;
                NewNode = Node;
                return true;
            }
        }
    }
}

void TNode::Print(int level,std::string &text){
    for(int i = 0;i < level;++i){
        std::cout << "\t";
    }
    for(int i = Start; i < *End; ++i){
        std::cout << text[i];
    }
    std::cout << std::endl;
    for(auto& child: Children){
        child.second->Print(level + 1, text);
    }
}

void TSuffTree::Print(){
    Root->Print(0,Text);
}