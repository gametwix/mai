#include <iostream>
#include <iomanip>

namespace NCarnum
{
    class TCarnum
    {
        public:
        int num;
        char sym[3];

        TCarnum()
        {
            num = 0;

            for(int i=0;i<3;++i)
            {
                sym[i] = 'A';
            }
        }

        friend std::istream& operator>>(std::istream &in, TCarnum &carnum)
        {
            in >> carnum.sym[0] >> carnum.num >> carnum.sym[1] >> carnum.sym[2];
            return in;
        }

        friend std::ostream& operator<< (std::ostream &out, const TCarnum &carnum)
        {
            out << carnum.sym[0] << " " <<  std::setfill('0') << std::setw(3) << carnum.num << " " << carnum.sym[1] << carnum.sym[2];
            return out;
        }
        
    }; // class TCarnum

} // namespace NCarnum