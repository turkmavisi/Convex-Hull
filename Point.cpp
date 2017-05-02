#include <iostream>
#include <math.h>
#include "Point.h"

using namespace std;

Point::Point()
{
    x=0;
    y=0;
}

Point::Point(int a=0, int b=0)
{
    x=a;
    y=b;
}

int Point::getX()
{
    return x;
}

void Point::setX(int a)
{
    x=a;
}

int Point::getY()
{
    return y;
}

void Point::setY(int b)
{
    y=b;
}

float Point::preAngle(Point p, bool f)
{
    float dx, dy, dr, pi=3.141593;
    if(isSame(p)) return -pi*2;
    else
    {
        dx=float(x-p.x);
        dy=float(y-p.y);
        dr=sqrt(pow(dx,2)+pow(dy,2));

        if(f)
        {
            if(dx>0) return -pi*2;
            else return -asin(dy/dr);
        }
        else
        {
            if(dx<0) return -pi*2;
            else return asin(dy/dr);
        }
    }
}

float Point::polAngle(Point s)
{
    if(this->isSame(s)) return 0;
    else
    {
        float dx, dy, dr;
        dx=float(x-s.x);
        dy=float(y-s.y);
        dr=sqrt(pow(dx,2)+pow(dy,2));
        return acos(dx/dr);
    }
}

bool Point::isSame(Point p)
{
    if(x==p.x&&y==p.y) return true;
    else return false;
}

bool Point::isCCW(Point p, Point n)
{
    if((float((x-p.x)*(n.y-p.y)-(y-p.y)*(n.x-p.x)))>=0) return true;
    else return false;
}

Point Point::findNext(Point p, vector <Point> &v, bool f)
{
    Point n=p;
    for(unsigned int i=0; i<v.size(); i++)
    {
        if(v[i].isSame(p)) v.erase(v.begin()+i);
        else if((f)&&(v[i].preAngle(p,f)>=n.preAngle(p,f))) n=v[i];
        else if((!f)&&(v[i].preAngle(p,f)>=n.preAngle(p,f)))n=v[i];
    }

    return n;
}
