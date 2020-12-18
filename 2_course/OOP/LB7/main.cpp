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

    char filename[256];
    while(true)
    {
        size_t sw = -1;
        size_t sw2 = -1;
        size_t pos = -1;
        std::cout << "1 - Создать новый докимент" << std::endl;
        std::cout << "2 - Загрузить документ" << std::endl;
        std::cout << "3 - Сохранить документ" << std::endl;
        std::cout << "4 - Добавить фигуру" << std::endl;
        std::cout << "5 - Удалить фигуру" << std::endl;
        std::cout << "6 - Отменить действие" << std::endl;
        std::cout << "7 - Вывести фигуры" << std::endl;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "Введите номер: ";
        std::cin >> sw;
        if(sw == 0)
            break;
        else
            switch (sw)
            {
            case 1:
                doc.Create();
                break;
            case 2:
                doc.Create();
                std::cout << "Введите название файла: ";
                std::cin >> filename;
                Load(doc,filename);
                break;
            case 3:
                std::cout << "Введите название файла: ";
                std::cin >> filename;
                Save(doc,filename);
            case 4:
                std::cout << "Введите позицию: ";
                std::cin >> pos;
                std::cout << "1 - Ромб" << std::endl;
                std::cout << "2 - Пятиугольник" << std::endl;
                std::cout << "3 - Шестиугольник" << std::endl;
                std::cout << "Введите число: ";
                std::cin >> sw2;
                switch(sw2)
                {
                    case 1:
                        doc.Add(pos,Factory<int,Rhomb<int>>::CreatFig());
                        break;
                    case 2:
                        doc.Add(pos,Factory<int,Pentagon<int>>::CreatFig());
                        break;
                    case 3:
                        doc.Add(pos,Factory<int,Hexagon<int>>::CreatFig());
                        break;
                    default:
                        break;
                }
                break;
            case 5:
                std::cout << "Введите позицию: ";
                std::cin >> pos;
                doc.Del(pos);
                break;
            case 6:
                doc.Undo();
                break;
            case 7:
                for(int i = 0;i < doc.elems.size();++i)
                    doc.elems[i]->print();
                break;
            default:
                break;
            }
    } 
    return 0;
}