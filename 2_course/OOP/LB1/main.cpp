
#include <iostream>

using namespace std;

class BritishMoney 
{
    private:

        BritishMoney sum(const BritishMoney &a,const BritishMoney &b)
            {
                BritishMoney c;
                c.penny = (int)a.penny + (int)b.penny;
                c.shilling = (int)a.shilling + (int)b.shilling;
                c.pounds = a.pounds + b.pounds;
                c = norm(c);
                return c;
            }

        BritishMoney diff(BritishMoney a,BritishMoney b)
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
        
        BritishMoney norm(BritishMoney a)
        {
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

        double div(BritishMoney a,BritishMoney b)
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

    public:
        unsigned long long pounds;
        unsigned char shilling;
        unsigned char penny;
        BritishMoney()
        {
            this->pounds = 0;
            this->shilling = 0;
            this->penny = 0;
        }

        BritishMoney operator+(BritishMoney b)
        {
            return sum(*this,b);
        }

        BritishMoney operator-(BritishMoney b)
        {
            return diff(*this,b);
        }

        

        BritishMoney operator*(double b) 
        {
            int ostpenny = ((int)this->penny*b)/12;
            int ostshilling = ((int)this->shilling*b+ostpenny)/20;

            BritishMoney c;

            int shillingvozvr =  ((int)this->shilling)*b-(int)((int)this->shilling*b);
            int shillingvozvr_to_penny = (int)(shillingvozvr*12)%12;
            c.penny = (int)((int)this->penny*b)%12+shillingvozvr_to_penny;

            int poundvozvr =  this->pounds*b-(long long)(this->pounds*b);
            int poundvozvr_to_shilling = (int)(poundvozvr*12)%12;
            c.shilling = (int)((int)this->shilling*b+ostpenny)%20+poundvozvr_to_shilling;

            c.pounds = this->pounds*b+ostshilling;

            c = norm(c);
            
            return c;
        }

        BritishMoney operator/(double b)
        {
            BritishMoney c;
            c = *this * (1/b);
            return c;
        }

        double operator/(BritishMoney b)
        {
            return div(*this,b);
        }

        void operator =(const BritishMoney &b)
        {
            this->pounds = b.pounds;
            this->shilling = b.shilling;
            this->penny = b.penny;
        }

        bool operator==(const BritishMoney &b)
        {
            if(this->pounds == b.pounds && this->shilling == b.shilling && this->penny == b.penny)
                return true;
            else return false;
        }

        bool operator!=(const BritishMoney &b)
        {
            return !(*this == b);
        }


        bool operator>(const BritishMoney &b)
        {
            if(this->pounds > b.pounds) return true;
            else if(this->pounds == b.pounds)
            {
                if((int)this->shilling > (int)b.shilling) return true;
                else if((int)this->shilling == (int)b.shilling)
                {
                    if((int)this->penny > (int)b.penny) return true;
                    else false;
                }
                else return false;
            }
            else return false;
            return false;
        }

        bool operator<(const BritishMoney &b)
        {
            if(this->pounds < b.pounds) return true;
            else if(this->pounds == b.pounds)
            {
                if((int)this->shilling < (int)b.shilling) return true;
                else if((int)this->shilling == (int)b.shilling)
                {
                    if((int)this->penny < (int)b.penny) return true;
                    else false;
                }
                else return false;
            }
            else return false;
            return false;
        }

        bool operator>=(const BritishMoney &b)
        {
            return ((*this>b)||(*this==b));
        }

        bool operator<=(const BritishMoney &b)
        {
            return ((*this<b)||(*this==b));
        }


    
};



int main()
{

    BritishMoney a;
    BritishMoney b;
    a.pounds = 10;
    a.shilling = 13;
    a.penny = 7;
    a = a;
    b = a*2;
    cout << a/a << " " << a/b << " " << b/a << endl;
    return 0;
}