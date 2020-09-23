#include <iostream>


class BritishMoney 
{
    private:


        BritishMoney sum(const BritishMoney &a,const BritishMoney &b);

        BritishMoney diff(BritishMoney a,BritishMoney b);

        BritishMoney norm(BritishMoney a);
        
        double div(BritishMoney a,BritishMoney b);

        BritishMoney impl(const BritishMoney &a,double b);
        

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


        void print();
        

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
            return impl(*this,b);
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
