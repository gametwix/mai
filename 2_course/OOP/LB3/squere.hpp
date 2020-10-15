#include "figure.hpp"
class Squere: public Figure
{
    public:
    
    double size;

    Squere(double s)
    {
        size = s;
    }

    double Area() override;
    void Print_cord() override;
    Dot Center() override;
};