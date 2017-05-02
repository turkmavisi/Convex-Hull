#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED
#include <iostream>
#include "Point.h"

using namespace std;

class Line
{
    private:
        Point p1, p2;
    public:
        //Line(Point p, Point q);
        Point getP1();
        void setP1(Point);
        Point getP2();
        void setP2(Point);
};

#endif // LINE_H_INCLUDED
