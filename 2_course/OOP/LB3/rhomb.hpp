#include "figure.hpp"

class Rhomb: public Figure
{
    public:

    double diag_1;
    double diag_2;

    double Area() override;
    void Print_cord() override;
    Dot Center() override;
    void Cords(Dot* cord);
};

