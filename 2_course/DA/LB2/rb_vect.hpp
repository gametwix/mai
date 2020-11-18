#include <iostream>
#include <stdio.h>
#include <fstream>
#include "vector.hpp"
#pragma once

namespace rb
{
    template <typename T>
    class rb_tree_elem
    {
        public:
        bool Color;
        T Key;
        rb_tree_elem *Left;
        rb_tree_elem *Right;
        rb_tree_elem *Par;

        rb_tree_elem()
        {
            Color = 0;
            Left = nullptr;
            Right = nullptr;
            Par = nullptr;
        }
    };

    template <typename T>
    class rb_tree
    {
        public:
        rb_tree_elem<T> *Root;
        rb_tree_elem<T> *Nil;

        rb_tree()
        {
            Nil = new(rb_tree_elem<T>);
            Root = Nil;
        }

        void left_rotate(rb_tree &Tree,rb_tree_elem<T> *x)
        {
            rb_tree_elem<T> *y = x->Right;
            x->Right = y->Left;

            if (y->Left != Tree.Nil)
            {
                y->Left->Par = x;
            }

            y->Par = x->Par;

            if(x->Par == Tree.Nil)
            {
                Tree.Root = y;
            }
            else if(x == x->Par->Left)
            {
                x->Par->Left = y;
            }
            else
            {
                x->Par->Right = y;
            }
            y->Left = x;
            x->Par = y;
        }

        void right_rotate(rb_tree &Tree,rb_tree_elem<T> *y)
        {
            rb_tree_elem<T> *x = y->Left;
            y->Left = x->Right;

            if(x->Right != Tree.Nil)
            {
                x->Right->Par = y;
            }

            x->Par = y->Par;

            if(y->Par == Tree.Nil)
            {
                Tree.Root = x;
            }
            else if(y == y->Par->Left)
            {
                y->Par->Left = x;
            }
            else
            {
                y->Par->Right = x;
            }
            x->Right = y;
            y->Par = x;
        }

        void ins_fix(rb_tree &Tree,rb_tree_elem<T> *z)
        {
            while(z->Par->Color == 1)
            {
                if(z->Par == z->Par->Par->Left)
                {
                    rb_tree_elem<T> *y = z->Par->Par->Right;
                    if(y->Color == 1)
                    {
                        z->Par->Color = 0;
                        y->Color = 0;
                        z->Par->Par->Color = 1;
                        z = z->Par->Par;
                    }
                    else
                    {
                        if(z == z->Par->Right)
                        {
                            z = z->Par;
                            left_rotate(Tree,z);
                        }
                        z->Par->Color = 0;
                        z->Par->Par->Color = 1;
                        right_rotate(Tree,z->Par->Par);
                    }
                }
                else
                {
                    rb_tree_elem<T> *y = z->Par->Par->Left;
                    if(y->Color == 1)
                    {
                        z->Par->Color = 0;
                        y->Color = 0;
                        z->Par->Par->Color = 1;
                        z = z->Par->Par;
                    }
                    else
                    {
                        if(z == z->Par->Left)
                        {
                            z = z->Par;
                            right_rotate(Tree,z);
                        }
                        z->Par->Color = 0;
                        z->Par->Par->Color = 1;
                        left_rotate(Tree,z->Par->Par);
                    }
                }
            }
            Tree.Root->Color = 0;
        }

        void insert(rb_tree &Tree,rb_tree_elem<T> *z)
        {
            rb_tree_elem<T> *y = Tree.Nil;
            rb_tree_elem<T> *x = Tree.Root;
            while(x != Tree.Nil)
            {
                y = x;
                if(z->Key < x->Key)
                {
                    x = x->Left;
                }
                else
                {
                    x = x->Right;
                }
            }
            z->Par = y;
            if(y == Tree.Nil)
            {
                Tree.Root = z;
            }
            else if(z->Key < y->Key)
            {
                y->Left = z;
            }
            else
            {
                y->Right = z;
            }
            z->Left = Tree.Nil;
            z->Right = Tree.Nil;
            z->Color = 1;
            ins_fix(Tree,z);
        }

        void insert_data(T data)
        {
            rb_tree_elem<T> *z = new rb_tree_elem<T>;
            z->Key = data;
            insert(*this,z);
        }

        void print(rb_tree_elem<T> *Tree,int lvl)
        {
            if(Tree->Right!=this->Nil)
                print(Tree->Right,(lvl+1));
            for(int i=0;i<lvl;++i) std::cout << "\t";
            std::cout << Tree->Color << " " << Tree->Key <<std::endl;
            if(Tree->Left!=this->Nil)
                print(Tree->Left,(lvl+1));
        }

        void clear(rb_tree_elem<T> *Tree)
        {
            if(Tree->Left!=this->Nil)
                clear(Tree->Left);
            if(Tree->Right!=this->Nil)
                clear(Tree->Right);
            delete Tree;
        }

        void save_vect(rb_tree_elem<T> *Tree,NVector::TVector<T> &vect)
        {
            if(Tree->Left!=this->Nil)
                save_vect(Tree->Left,vect);
            
            vect.Push_back(Tree->Key);
            if(Tree->Right!=this->Nil)
                save_vect(Tree->Right,vect);
        }

        void save(char *ch)
        {
            NVector::TVector<T> vect;
            save_vect(this->Root,vect);
            size_t size = vect.Size();
            std::ofstream wf;
            wf.open(ch, std::ios::out | std::ios::binary);
            wf.write((char *) &size,sizeof(size_t));
            wf.write((char *) vect.Get_data(),vect.Size()*sizeof(T));
            wf.close();
        }

        void load(char *ch)
        {
            NVector::TVector<T> vect;
            std::ifstream rf;
            rf.open(ch, std::ios::out | std::ios::binary);
            size_t size;
            rf.read((char *) &size,sizeof(size_t));
            std::cout <<size<<std::endl;
            T *dat = new T[size];
            std::cout <<"Test"<<std::endl;
            rf.read((char *) dat,sizeof(T)*size);
            std::cout <<"Test"<<std::endl;
            vect.Set(dat,size);
            load_vect(vect);
            rf.close();
        }
        
        void load_vect(NVector::TVector<T> &vect)
        {
            this->clear(this->Root);
            this->Root = this->Nil;
            for(int i=0;i<vect.Size();++i)
            {
                insert_data(vect[i]);
            }   
        }

        T& Search(const T& sample,bool& success)
        {
            rb_tree_elem<T> *x = this->Root;
            while(x != Tree.Nil)
            {   
                if(x == sample)
                {
                    success = true;
                    return x;
                }
                else
                {
                    if(sample < x->Key)
                    {
                        x = x->Left;
                    }
                    else
                    {
                        x = x->Right;
                    }
                }
                success = false;
                return sample;
            }
        }
    };

}//namespace rb