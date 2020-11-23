#include <iostream>
#include "queue.hpp"

int main()
{
    Queue<int> q;

    q.Push(1);
    q.Push(2);
    q.Push(3);

    q.Pop();
    q.Pop();
    q.Pop();

    Queue<int>::iterator a;

    return 0;
}