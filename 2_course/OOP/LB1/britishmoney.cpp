#include "britishmoney.hpp"


BritishMoney BritishMoney::sum(const BritishMoney &a,const BritishMoney &b)
{
    BritishMoney c;
    c.penny = (int)a.penny + (int)b.penny;
    c.shilling = (int)a.shilling + (int)b.shilling;
    c.pounds = a.pounds + b.pounds;
    c = norm(c);
    return c;
}

BritishMoney BritishMoney::diff(BritishMoney a,BritishMoney b)
{
    BritishMoney c;
    if(a>b)
    {
        int minusshilling = 0;
        int minuspound = 0;
        if((int)a.penny<(int)b.penny)
        {
            minusshilling = 1;
            c.penny=(int)a.penny+12-(int)b.penny;
        }
        else c.penny=(int)a.penny-(int)b.penny;
        
        if((int)a.shilling-minusshilling<(int)b.penny)
        {
            minuspound = 1;
            c.shilling=(int)a.shilling-(int)b.shilling+20;
        }
        c.pounds=a.pounds-b.pounds-minuspound;
    }
    return c;
}

BritishMoney BritishMoney::norm(BritishMoney a)
{
    //если количество монет больше максимума,то переносим на больший разряд
    if((int)a.penny>=12)
        {
            a.shilling += (int)a.penny/12;
            a.penny = (int)a.penny%12;
        }
        if((int)a.shilling>=20)
        {
            a.pounds += (int)a.shilling/20;
            a.shilling = (int)a.shilling%20;
        }
    return a;
}

double BritishMoney::div(BritishMoney a,BritishMoney b)
{
    double c = 0;
    const BritishMoney nul;
    while(a>=b)
    {
        ++c;
        a = a - b;
    }

    if(a!=nul)
    {
        c = c + 1/div(b,a);
    }

    return c;

}

void BritishMoney::print()
{
    std::cout << this->pounds << " " << (int)this->shilling << " " << (int)this->penny << std::endl;    
}

BritishMoney BritishMoney::impl(const BritishMoney &a,double b)
{
            BritishMoney c;

            //значения без переносов
            c.penny = (int)((int)a.penny*b)%12; 
            c.shilling = (int)((int)a.shilling*b)%20;
            c.pounds = (unsigned long long)(a.pounds*b);


            //остатки от умножения на дробное число
            double ost_pound = (int)a.pounds*b - c.pounds;
            double ost_shilling = a.shilling*b - (int)((int)a.shilling*b);

            //приведение остатка фунтов в шиллинги и пенни
            int pound_to_shilling = (int)(ost_pound*20);
            int pound_to_penny = (int)((ost_pound*20 - pound_to_shilling)*12);

            //приведение остатка шиллингов в пенни
            int shilling_to_penny = (int)(ost_shilling*12);

            //приведение лишних пенни в шиллинги и фунты
            int penny_to_shilling = ((int)((int)a.penny*b)/12)%20;
            unsigned long long penny_to_pound = (unsigned long long)(((int)((int)a.penny*b)/12 - penny_to_shilling)/20);

            //приведение лишних шиллингов в фунты 
            unsigned long long shilling_to_puond = (int)((int)a.shilling*b)/20;

            //прибавляем остатки
            c.penny += pound_to_penny + shilling_to_penny;
            c.shilling += pound_to_shilling + penny_to_shilling;
            c.pounds += penny_to_pound + shilling_to_puond;

            //переносим к нормальному виду
            c = norm(c);
            
            return c;
        }
