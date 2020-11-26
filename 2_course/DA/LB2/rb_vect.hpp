#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>



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

        ~rb_tree()
        {
            clear(Root);
            delete Nil;
        }

        void left_rotate(rb_tree &Tree,rb_tree_elem<T> *x)
        {
            rb_tree_elem<T> *y = x->Right;
            if(x == Root)
                Root = y;
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
            if(y == Root)
                Root = x;
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
            //Tree.Root->Par = Nil;
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

        void transplant(rb_tree_elem<T> *u,rb_tree_elem<T> *v)
        {
            if(u->Par == Nil)
                Root = v;
            else if(u == u->Par->Left)
                u->Par->Left = v;
            else
                u->Par->Right = v;
            v->Par = u->Par;
        }

        

        void insert_data(T data)
        {
            rb_tree_elem<T> *z = new rb_tree_elem<T>;
            z->Key = data;
            insert(*this,z);
        }

        void print(rb_tree_elem<T> *Tree,int lvl)
        {
            if(Tree->Right!=Nil)
                print(Tree->Right,(lvl+1));
            for(int i=0;i<lvl;++i) std::cout << "\t";
            std::cout << Tree->Color << " " << Tree->Key <<std::endl;
            if(Tree->Left!=Nil)
                print(Tree->Left,(lvl+1));
        }

        void clear(rb_tree_elem<T> *Tree)
        {
            if(Tree->Left!=Nil)
                clear(Tree->Left);
            if(Tree->Right!=Nil)
                clear(Tree->Right);
            delete Tree;
        }

        void save_tree(rb_tree_elem<T> *Tree,std::ofstream& wf)
        {
            bool have_left = (Tree->Left != Nil);
            bool have_right = (Tree->Right != Nil);

            wf.write((char *) &have_left, sizeof(bool));
            wf.write((char *) &have_right, sizeof(bool));

            wf.write((char *) &Tree->Key, sizeof(T));
            wf.write((char *) &Tree->Color, sizeof(bool));
            
            if(have_left)
                save_tree(Tree->Left,wf);
            if(have_right)
                save_tree(Tree->Right,wf);
        }

        void save(char *ch)
        {
            std::ofstream wf;
            wf.open(ch, std::ios::out | std::ios::binary);
            save_tree(Root,wf);
            wf.close();
        }

        void load_tree(rb_tree_elem<T> *Tree,std::ifstream& rf)
        {
            bool have_left;
            bool have_right;
            rf.read((char *) &have_left, sizeof(bool));
            rf.read((char *) &have_right, sizeof(bool));

            rf.read((char *) &Tree->Key, sizeof(T));
            rf.read((char *) &Tree->Color, sizeof(bool));

            if(have_left)
            {
                Tree->Left = new rb_tree_elem<T>;
                Tree->Left->Left = Nil;
                Tree->Left->Right = Nil;
                Tree->Left->Par = Tree;
                load_tree(Tree->Left,rf);
            }

            if(have_right)
            {
                Tree->Right = new rb_tree_elem<T>;
                Tree->Right->Left = Nil;
                Tree->Right->Right = Nil;
                Tree->Left->Par = Tree;
                load_tree(Tree->Right,rf);
            }
        }

        void load(char *ch)
        {
            std::ifstream rf;
            rf.open(ch, std::ios::out | std::ios::binary);
            clear(Root);
            Root = new rb_tree_elem<T>;
            Root->Par = Nil;
            Root->Left = Nil;
            Root->Right = Nil;
            load_tree(Root,rf);
            rf.close();
        }
        
        

        rb_tree_elem<T>* Search(const T& sample,bool& success)
        {
            rb_tree_elem<T> *x = Root;
            while(x != Nil)
            {   
                if(x->Key == sample)
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
            }
            success = false;
            return x;
        }

        rb_tree_elem<T>* Tree_min(rb_tree_elem<T>* elem)
        {
            while(elem->Left != Nil)
                elem = elem->Left;

            return elem;
        }

        void rb_delete(rb_tree_elem<T>* &elem)
        {
            rb_tree_elem<T>* y = elem;
            rb_tree_elem<T>* x;
            bool y_orig_color = y->Color;
            if(elem->Left == Nil)
            {
                x = elem->Right;
                transplant(elem,elem->Right);
            }
            else if(elem->Right == Nil)
            {
                rb_tree_elem<T>* x = elem->Left;
                transplant(elem,elem->Left);
            }
            else 
            {
                y = Tree_min(elem->Right);
                y_orig_color = y->Color;
                x = y->Right;
                if(y->Par == elem)
                {
                    x->Par = y;
                }
                else
                {
                    transplant(y,y->Right);
                    y->Right = elem->Right;
                    y->Right->Par = y;
                }
                y->Left = elem->Left;
                y->Left->Par = y;
                y->Color = elem->Color;
                if(elem == Root)
                    Root = y;
            }

            if(y_orig_color == 0)
                {
                    delete_fix(x);
                }
            delete elem;
        }

        void delete_fix(rb_tree_elem<T>* &x)
        {
            while((x != Root) && (x->Color == 0))
            {
                if(x == x->Par->Left)
                {
                    rb_tree_elem<T>* w = x->Par->Right;
                    if(w->Color == 1)
                    {
                        w->Color = 0;
                        x->Par->Color = 1;
                        left_rotate(*this,x->Par);
                        if(Root == x->Par)
                            Root = x->Par->Par;
                        w = x->Par->Right;
                    }
                    if((w->Left->Color == 0) && (w->Right->Color == 0))
                    {
                        w->Color = 1;
                        x = x->Par;
                    }
                    else 
                    {
                        if(w->Right->Color == 0)
                        {
                            w->Left->Color = 0;
                            w->Color = 1;
                            right_rotate(*this,w);
                            if(w == Root)
                                Root = w->Par;
                            w = x->Par->Right;
                        }
                        w->Color = x->Par->Color;
                        x->Par->Color = 0;
                        w->Right->Color = 0;
                        left_rotate(*this,x->Par);
                        if(Root == x->Par)
                            Root = x->Par->Par;
                        x = Root;
                    }
                }
                else
                {
                    rb_tree_elem<T>* w = x->Par->Left;
                    if(w->Color == 1)
                    {
                        w->Color = 0;
                        x->Par->Color = 1;
                        right_rotate(*this,x->Par);
                        if(Root == x->Par)
                            Root = x->Par->Par;
                        w = x->Par->Left;
                    }
                    if((w->Right->Color == 0) && (w->Left->Color == 0))
                    {
                        w->Color = 1;
                        x = x->Par;
                    }
                    else 
                    {
                        if(w->Left->Color == 0)
                        {
                            w->Right->Color = 0;
                            w->Color = 1;
                            left_rotate(*this,w);
                            if(w == Root)
                                Root = w->Par;
                            w = x->Par->Left;
                        }
                        w->Color = x->Par->Color;
                        x->Par->Color = 0;
                        w->Left->Color = 0;
                        right_rotate(*this,x->Par);
                        if(Root == x->Par)
                            Root = x->Par->Par;
                        x = Root;
                    }
                }
            }
        }

        void Delete(const T& sample)
        {
            bool sucs = false;
            rb_tree_elem<T>* elem  = nullptr;
            elem = Search(sample,sucs);
            if(sucs)
            {
                rb_delete(elem);
            }
        }
    };

    

}//namespace rb