#include <iostream>
#include <vector>
#include "factory.hpp"
#include "Figure.hpp"
#include "Pentagon.hpp"
#include "Rhomb.hpp"
#include "Action.hpp"

template <typename T>
void Save(Document<Figure<T>> &doc,char* FileName)
{
    std::ofstream file(FileName,std::ios::binary);
    std::cout << doc.elems.size() <<std::endl;
    for(int i = 0;i < doc.elems.size();++i)
    {
        std::cout << i <<std::endl;
        doc.elems[i]->write(file);
    }
    file.close();
}

template <typename T>
void Load(Document<Figure<T>> &doc,char* FileName)
{
    std::ifstream file(FileName,std::ios::binary);
    int i = 0;
    while(file.peek() != EOF)
    {
        size_t TYPE;
        file.read((char*) &TYPE,sizeof(size_t));        
        if(TYPE == 0)
        {
            std::pair<T,T> C;
            T S;
            file.read((char*) &(C.first), sizeof (T));
            file.read((char*) &(C.second), sizeof (T));
            file.read((char*) &(S), sizeof (T));
            doc.Add(i,Factory<T,Pentagon<T>>::ReadFig(C,S));
        }
        else if(TYPE == 1)
        {
            std::pair<T,T> C;
            T D1,D2;
            file.read((char*) &(C.first), sizeof (T));
            file.read((char*) &(C.second), sizeof (T));
            file.read((char*) &(D1), sizeof (T));
            file.read((char*) &(D2), sizeof (T));
            doc.Add(i,Factory<T,Rhomb<T>>::ReadFig(C,D1,D2));
        }
        else if(TYPE == 2)
        {
            std::pair<T,T> C;
            T S;
            file.read((char*) &(C.first), sizeof (T));
            file.read((char*) &(C.second), sizeof (T));
            file.read((char*) &(S), sizeof (T));
            doc.Add(i,Factory<T,Hexagon<T>>::ReadFig(C,S));
        }
        ++i;
    }
    file.close();
}

int main()
{
    Document<Figure<int>> doc;
    //doc.Add(0,Factory<int,Rhomb<int>>::CreatFig());
    //doc.Add(0,Factory<int,Pentagon<int>>::CreatFig());
    char name[10] = "test.b";
    //Save(doc,name);
    Load(doc,name);
    for(int i = 0;i < doc.elems.size();++i)
        doc.elems[i]->print();
    std::cout << "-------------" <<std::endl;   
    doc.Del(1);
    for(int i = 0;i < doc.elems.size();++i)
        doc.elems[i]->print();
    std::cout << "-------------" <<std::endl;   
    doc.Undo();
    for(int i = 0;i < doc.elems.size();++i)
        doc.elems[i]->print();
    std::cout << "-------------" <<std::endl;   
    return 0;
}