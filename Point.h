#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Point
{
    private:
        int x, y;
    public:
        Point();
        Point(int, int);
        int getX();
        void setX(int);
        int getY();
        void setY(int);
        float preAngle(Point, bool);
        float polAngle(Point);
        bool isSame(Point);
        bool isCCW(Point, Point);
        Point findNext(Point, vector <Point>&, bool);
};

#endif // POINT_H_INCLUDED
