#pragma once

#include <memory>
#include <iostream>
#include "allocator.hpp"

template <class T>
class Queue
{
    private:
        
        struct Queue_elem
        {
            T key;
            std::shared_ptr<Queue_elem> next;
            std::shared_ptr<Queue_elem> prev;

            //static alloc::custom_allocator<Queue_elem,20> al;
            static alloc::custom_allocator<Queue_elem,20> &get_allocator()
            {
                static alloc::custom_allocator<Queue_elem,20> al;
                return al;
            }
            
            

                Queue_elem()
                {
                    next = nullptr;
                    prev = nullptr;
                }
                Queue_elem(const T data)
                {
                    key = data;
                    next = nullptr;
                    prev = nullptr;
                }

                void* operator new(size_t size)
                {
                    return get_allocator().allocate();
                }
                void operator delete(void* point)
                {
                    get_allocator().deallocate((Queue_elem*)point);
                }
        };

    size_t size = 0;
    std::shared_ptr<Queue_elem> start;
    std::shared_ptr<Queue_elem> finish;
    std::shared_ptr<Queue_elem> Nil;
    



    Queue_elem* Top()
    {
        return start;
    }

    public:

        Queue()
        {
            start = nullptr;
            finish = nullptr;
            Nil = std::shared_ptr<Queue_elem>(new Queue_elem);
            Nil->prev = nullptr;
            Nil->next = start;
        }


        void Push(const T& data)
        {
            Queue_elem* l = new Queue_elem(data);
            std::shared_ptr<Queue_elem> elem(l);
            if(start == nullptr)
            {
                finish = elem;
            }
            else
            {
                elem->next = start;
                start->prev = elem;
            }
            elem->prev = Nil;
            Nil->next = elem;
            start = elem;
            ++size;
        }


        T Pop()
        {
            if(finish == nullptr)
            {
                throw -1;
            }
            T data = finish->key;
            if(finish->prev == Nil)
            {
                finish = nullptr;
                start = nullptr;
            }
            else
            {
                finish = finish->prev;
            }
            --size;
            return data;
        }

        class iterator
        {
            
            Queue_elem* data_iter;
            public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

                iterator()
                {
                    data_iter = nullptr;
                }
                
                iterator(Queue_elem* second)
                {
                    data_iter = second;
                }

                T*& operator->()
                {
                    return &data_iter->key;
                }

                T& operator*()
                {
                    return data_iter->key;
                }

                bool operator==(const iterator &second)
                {
                    return (data_iter == second.data_iter);
                }

                bool operator==(const T* &second)
                {
                    return (data_iter == second);
                }

                bool operator!=(const iterator &second)
                {
                    return (data_iter != second.data_iter);
                }

                bool operator!=(const T* &second)
                {
                    return (data_iter != second);
                }

                void operator=(const iterator &second)
                {
                    data_iter = second.data_iter;
                }

                void operator=(const T* &second)
                {
                    data_iter = second;
                }

                iterator operator++()
                {
                    if(data_iter == nullptr)
                    {
                        throw -1;
                    }
                    data_iter = data_iter->prev.get();
                    return iterator(data_iter);
                }

                iterator operator--()
                {
                    if(data_iter == nullptr)
                    {
                        throw -1;
                    }
                    data_iter = data_iter->next.get();
                    return iterator(data_iter);
                }

                iterator operator+(const size_t &ind)
                {
                    iterator it(data_iter);
                    for(int i=0;i<ind;++i)
                    {
                        if(it.data_iter == nullptr)
                        {
                            throw -1;
                        }
                        it.data_iter = it.data_iter->prev.get();
                    }
                    return it;
                }

                iterator operator-(const size_t &ind)
                {
                    iterator it(data_iter);
                    for(int i=0;i<ind;++i)
                    {
                        if(it.data_iter == nullptr)
                        {
                            throw -1;
                        }
                        it.data_iter = it.data_iter->next.get();
                    }
                    return it;
                }
        };

        iterator Begin()
        {
            return iterator(finish.get());
            
        }

        iterator End()
        {
            iterator iter = start.get();
            ++iter;
            return (iter);
        }

        void Insert(iterator it,T data)
        {
            if((it == nullptr) || (it == Nil.get()))
                Push(data);
            else
            {
                Push(T());
                for(iterator iter = End() - 1;iter != it;--iter)
                {
                    *iter = *(iter-1);
                }
                *it = data;
            }
            
        }

        void Erase(iterator it)
        {
            if((it == nullptr) || (it == Nil.get()))
            {
                throw -1;
            }
            for(iterator iter = it;iter != Begin();--iter)
            {
                *iter = *(iter-1);
            }
            Pop();
        }

        int Size()
        {
            return size;
        }
};