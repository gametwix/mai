#include "figure.hpp"

class Rhomb: public Figure
{
    public:

    double size;
    double big_angle;

    double Area() override;
    void Print_cord() override;
    Dot Center() override;
    void Cords(Dot* cord);
};

