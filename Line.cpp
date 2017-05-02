#include <iostream>
#include "Point.h"
#include "Line.h"

using namespace std;
/*
Line::Line(Point p, Point q)
{
    p1=p;
    p2=q;
}
*/
Point Line::getP1()
{
    return p1;
}

void Line::setP1(Point p)
{
    p1=p;
}

Point Line::getP2()
{
    return p2;
}

void Line::setP2(Point q)
{
    p2=q;
}
