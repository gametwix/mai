#include <iostream>
#include <algorithm>
#include "queue.hpp"
#include "squere.hpp"

int main()
{
    Queue<Square<int>> que;
/*
    q.Push(1);
    q.Push(2);
    q.Push(3);

    q.Insert((q.Begin()+1),5);
    q.Erase(q.Begin()+2);



    //Queue<int>::iterator a = q.Begin();




    auto print = [](int n) { std::cout << " " << n; };
    std::for_each(q.Begin(),q.End(),print);

    ///std::cout << 1;
    for (Queue<int>::iterator iter = q.Begin(); iter != q.End(); ++iter)
    {
        std::cout <<*iter << std::endl;
    }*/


     while(true)
    {
        int sw=-1;
        Square<int> sq;
        int pos = 0;
        
        int minimal_suare = 0;
        auto print = [](Square<int> n) { std::cout << n << std::endl; };
        

        std::cout << "0 - Выход" << std::endl;
        std::cout << "1 - Добавить квадрат в конец очереди" << std::endl;
        std::cout << "2 - Добавить квадрат по индексу" << std::endl;
        std::cout << "3 - Удалить квадрат в начале очереди" << std::endl;
        std::cout << "4 - Удалить квадрат по индексу" << std::endl;
        std::cout << "5 - Вывести очередь" << std::endl;
        std::cout << "6 - Вывести количество квадратов площадь которых меньше указанной" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> sw;

        if(sw == 0) break;
        else
        {
            switch (sw)
            {
            case 1:
                std::cout << "Введите длину стороны квадрата:";
                std::cin >> sq;
                que.Push(sq);
                std::cout << "Добавление произведено успешно" << std::endl;
                break;
            case 2:
                std::cout << "Введите длину стороны квадрата:" ;
                std::cin >> sq;
                std::cout << "Введите индекс:" ;
                std::cin >> pos;
                try
                {
                    que.Insert(que.Begin()+(pos-1),sq);
                    std::cout << "Добавление произведено успешно" << std::endl;
                }
                catch(int exs)
                {
                    std::cout << "Выход за допустимую границу коллекции" << std::endl;
                }
                break;
            case 3:
                que.Pop();
                std::cout << "Удаление произведено успешно" << std::endl;

                break;
            case 4:
                std::cout << "Введите индекс:";
                std::cin >> pos;
                try
                {
                    que.Erase(que.Begin()+(pos-1));
                    std::cout << "Удаление произведено успешно" << std::endl;
                }
                catch(int exs)
                {
                    std::cout << "Выход за допустимую границу коллекции" << std::endl;
                }
            case 5:
                
                std::for_each(que.Begin(),que.End(),print);
                break;
            case 6:
            
                
                std::cout << "Введите минимальную площадь:" ;
                std::cin >> minimal_suare;
                auto figures_less_squre = [minimal_suare](Square<int> n) { return (n.square() < minimal_suare); };
                std::cout << "Количество квадратов площадь которых меньше указанной: " << std::count_if(que.Begin(), que.End(), figures_less_squre) << std::endl;

                
            
            }
        }
    }



    return 0;
}