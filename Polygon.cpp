#include <iostream>
#include <vector>
#include "Point.h"
#include "Polygon.h"

using namespace std;

Polygon::Polygon(vector<Point> pSet)
{
    pntSet=pSet;
}

void Polygon::addPoint(Point pAdd)
{
    pntSet.push_back(pAdd);
}

void Polygon::delPoint(int pID)
{
    pntSet.erase(pntSet.begin()+pID);
}

int Polygon::getNumOfPoints()
{
    return pntSet.size();
}

Point Polygon::getPoint(int pID)
{
    return pntSet[pID];
}

void Polygon::setPoints(vector<Point>& pSet)
{
    pntSet=pSet;
}
