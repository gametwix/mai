#include <iostream>
#include <string>
#include "rb_vect.hpp"
#include "vector.hpp"
#include <stdio.h> 

class T2
{
    public:
    int key;
    T2 *l;
};

class Test
{
    public:
    T2 a[3];
};
int main()
{
    rb::rb_tree<int> tree;
    NVector::TVector<int> vec;
    for(int i=0;i<5;++i)
    {
        int a;
        std::cin >> a;
        tree.insert_data(a);
    }
    char l[7] = "./r.b";
    tree.save(l);
    tree.print(tree.Root,0);

    for(int i=0;i<vec.Size();++i)
    {
        std::cout << vec[i] << std::endl;
    }

    for(int i=0;i<5;++i)
    {
        int a;
        std::cin >> a;
        tree.insert_data(a);
    }
    tree.print(tree.Root,0);
    tree.load(l);
    tree.print(tree.Root,0);
    //tree.print(tree.Root,0);
    //FILE *f;
    //f=fopen("./t.b", "wb");
    //fwrite(&tree, sizeof(rb::rb_tree<int>), 1, f);
    //fclose(f);

    //f=fopen("./t.b", "rb");
    //rb::rb_tree<int> tr;
    //fread(&tr, sizeof(rb::rb_tree<int>), 1, f);
    //fclose(f);
    
    /*Test T;
    T.a[0].key = 0;
    T.a[1].key = 1;
    T.a[2].key = 2;
    T.a[0].l = &T.a[1];
    T.a[1].l = &T.a[2];
    T.a[2].l = &T.a[0];
    FILE *f;
    f=fopen("./t.b", "wb");
    fwrite(&T, sizeof(Test), 1, f);
    fclose(f);
    f=fopen("./t.b", "rb");
    T.a[2].key = 5;
    fread(&T, sizeof(Test), 1, f);
    fclose(f);
    std::cout <<T.a[0].l->l->key << std::endl;*/

    
    return 0;
}