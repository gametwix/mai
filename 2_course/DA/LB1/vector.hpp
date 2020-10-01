#include <cstddef>
#include <initializer_list>


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
        int Size();
        T& operator [](size_t iter);


        //TVector(std::initializer_list<T> list);

    }; // class TVector

    template <typename T>
    TVector<T>::TVector()
    {
        Size_data = 0;
        Size_malloc = 0;
        Data = nullptr;
    }

    /*template <typename T>
    TVector<T>::TVector(std::initializer_list<T> list)
    {
        Size_data = list.size();
        Size_malloc = list.size();
        (*this).Resize(Size_malloc);
        int i = 0;
        for(x : list)
        {
            Data[i] = x;
            ++i;
        }
    }*/

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
    void TVector<T>::Copy(T* old_data, size_t begin, size_t end, T* new_data)    
    {
        size_t new_size = sizeof(new_data) / sizeof(T);
        for(size_t i = 0; i < (end - begin);++i)
        {
            if(i<new_size)
            {
                new_data[i] = old_data[begin+i];
            }
            else
                break;
        }
    }


    template <typename T>
    void TVector<T>::Resize(T*& old_data, size_t old_size, size_t new_size)
    {
        T * new_data = new T[new_size];
        Copy(old_data,0,min(old_size,new_size),new_data);
        delete old_data;
        old_data = new_data;
    }


    template <typename T>
    void TVector<T>::Resize(size_t new_size)
    {
        Resize(this->Data,Size_malloc,new_size);
        Size_malloc = new_size;
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
                Resize(Data,Size_malloc,Size_malloc*2);
                ++Size_malloc;
            }

           
        }

        Data[Size_data] = ins;
        
        ++Size_data;
    }

    template <typename T>
    T& TVector<T>::operator [](size_t iter)
    {
        if(iter < Size_data && iter >= 0)
            return Data[iter];
        else
        {
            T *err = new T;
            return *err;   
        }           
    }

} // namespace NVector


