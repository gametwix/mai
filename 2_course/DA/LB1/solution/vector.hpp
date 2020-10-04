#include <cstddef>
#include <initializer_list>
#include <iostream>


namespace NVector
{
    int min(int first, int second)
    {
        if(first < second)
            return first;
        else
            return second;
    }

    template <typename T>
    class TVector
    {
        protected:

        T *Data;                //Укачатель на массив объектов
        size_t Size_data;       //Длина массива
        size_t Size_malloc;     //Доступная длина

        void Resize(T*& old_data, size_t old_size, size_t new_size);
        void Copy(T* old_data, size_t begin, size_t end, T* new_data);

        public:

        void Resize(size_t new_size);
        TVector();
        int Begin();
        int End();
        void Push_back(T ins);
        T& operator [](size_t iter);


        void operator=(TVector<T> second_vect)
        {
            //delete(Data);
            Data = nullptr;
            Size_data = 0;
            Size_malloc = 0;
            for(int i = 0;i<second_vect.End();++i)
            {
                Push_back(second_vect.Data[i]);
            }
            //delete(second_vect.Data);
        }
        

    

    }; // class TVector

    template <typename T>
    TVector<T>::TVector()
    {
        Size_data = 0;
        Size_malloc = 0;
        Data = nullptr;
    }

    
    template <typename T>
    int TVector<T>::Begin()
    {
        return 0;
    }

    template <typename T>
    int TVector<T>::End()
    {
        return Size_data;
    }


    template <typename T>
    void TVector<T>::Copy(T* &old_data, size_t begin, size_t end, T* &new_data)    
    {
       
        for(size_t i = 0; i < (end - begin);++i)
        {
            new_data[i] = old_data[begin+i];
        }
    }


    template <typename T>
    void TVector<T>::Resize(T*& old_data, size_t old_size, size_t new_size)
    {
        T * new_data = new T[new_size];
        Copy(old_data,0,min(old_size,new_size),new_data);
        delete(old_data);
        old_data = new_data;
        new_data = nullptr;
    }


    template <typename T>
    void TVector<T>::Resize(size_t new_size)
    {
        Resize(this->Data,Size_malloc,new_size);
        Size_malloc = new_size;
        Size_data = new_size;
    }

    

    template <typename T>
    void TVector<T>::Push_back(T ins)
    {
        if (Size_data+1 > Size_malloc)
        {
            if(Size_malloc != 0)
            { 
                Resize(Data,Size_malloc,Size_malloc*2);
                Size_malloc*= 2;
            }
            else
            { 
                Resize(Data,Size_malloc,Size_malloc+1);
                ++Size_malloc;
            }

           
        }

        Data[Size_data] = ins;
        
        ++Size_data;
    }



    /*template <typename T>
    void TVector<T>::operator delete(TVector<T> vec)
    {
        delete(vec.Data);
    }
*/
    template <typename T>
    T& TVector<T>::operator [](size_t iter)
    {
        if(iter < Size_data && iter >= 0)
            return Data[iter];
        else
        {
            T *err = nullptr;
            return *err;   
        }           
    }

} // namespace NVector


