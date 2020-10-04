#include <iostream>
#include <iomanip>

namespace NCarnum
{
    class TCarnum
    {
        public:
        int Num;
        char Sym[3];

        TCarnum()
        {
            Num = 0;

            for(int i=0;i<3;++i)
            {
                Sym[i] = 'A';
            }
        }

        void operator=(TCarnum &second_elem)
        {
            this->Num = second_elem.Num;
            for(int i=0;i<3;++i)
            {
                this->Sym[i] = second_elem.Sym[i];
            }
        }

        friend std::istream& operator>>(std::istream &in, TCarnum &carnum)
        {
            in >> carnum.Sym[0] >> carnum.Num >> carnum.Sym[1] >> carnum.Sym[2];
            return in;
        }

        friend std::ostream& operator<< (std::ostream &out, const TCarnum &carnum)
        {
            out << carnum.Sym[0] << " " <<  std::setfill('0') << std::setw(3) << carnum.Num << " " << carnum.Sym[1] << carnum.Sym[2];
            return out;
        }
        
    }; // class TCarnum

} // namespace NCarnum