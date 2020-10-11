
namespace NIP
{
    class IPAddress
    {
        protected:
        unsigned char bites[4];

        //Конструкторы
        IPAddress();
        IPAddress(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4);
        IPAddress(const IPAddress& b);

        //Оператор присваивания
        void operator =(const IPAddress& b);
        //Оператор возврата битов
        unsigned char& operator [](int i); 
        //Оператовы арифметических действий 
        IPAddress operator +(const IPAddress& b);
        IPAddress operator -(const IPAddress& b);
        //Операторы сравнения 
        bool operator ==(const IPAddress& b);
        bool operator >(const IPAddress& b);
        bool operator <(const IPAddress& b);
        bool operator >=(const IPAddress& b);
        bool operator <=(const IPAddress& b);


        //Коньюнкция по маске
        void from_mask(const IPAddress& mask);

        bool ip_in_net(const IPAddress& ip_net,const IPAddress& mask);

    }; //class TIP
} //namespace NIP