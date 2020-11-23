#pragma once

#include <memory>


template <typename T>
class Queue
{
    private:

        template <typename Q>
        struct Queue_elem
        {
            Q key;
            std::shared_ptr<Queue_elem<Q>> next;
            std::shared_ptr<Queue_elem<Q>> prev;

                Queue_elem()
                {
                    next = nullptr;
                    prev = nullptr;
                }
                Queue_elem(const int data)
                {
                    key = data;
                    next = nullptr;
                    prev = nullptr;
                }
        };

    size_t size = 0;
    std::shared_ptr<Queue_elem<T>> start;
    std::shared_ptr<Queue_elem<T>> finish;


    Queue_elem<T>* Top()
    {
        return finish;
    }

    public:

        Queue()
        {
            start = nullptr;
            finish = nullptr;
        }


        void Push(const T& data)
        {
            std::shared_ptr<Queue_elem<T>> elem(new Queue_elem<T>(data));
            if(start == nullptr)
            {
                start = elem;
                finish = elem;
            }
            else
            {
                elem->next = start;
                start->prev = elem;
                start = elem;
            }
            ++size;
        }


        T Pop()
        {
            T data = finish->key;
            if(finish->prev == nullptr)
            {
                finish = nullptr;
                start = nullptr;
            }
            else
            {
                finish = finish->prev;
                finish->next = nullptr;
            }
            --size;
            return data;
        }

        class iterator
        {
            T* data_iter;
            public:
                T* operator->()
                {
                    return data_iter;
                }

                T* operator*()
                {
                    return *data_iter;
                }

                bool operator==(const iterator& second)
                {
                    return data_iter == second.data_iter;
                }

                bool operator==(const T& second)
                {
                    return data_iter == second;
                }
        };




};