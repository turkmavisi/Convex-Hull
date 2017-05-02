#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "BasicIO.h"
#include "GeomImage.h"
#include "Point.h"
#include "Polygon.h"

using namespace std;

void Home();
void ConvexHullJarvis();
void ConvexHullGraham();
bool compAngle(Point p, Point q);
Point o;
bool f;

int main()
{
    Home();
    system("pause");
    return 0;
}

void Home()
{
    string opt;
    cout << "Please choose a convex hull algorithm." << endl;
    cout << "Press 1 for Jarvis' march (gift wrapping) algorithm (with O(nh) complexity)." << endl;
    cout << "Press 2 for Graham's scan algorithm (with O(nlogn) complexity)." << endl;
    cout << "Press 0 to exit." << endl;
    getline(cin, opt);

    if(opt=="0") exit(EXIT_SUCCESS);
    else if (opt=="1")
    {
        cout << endl << "You chose the Jarvis' march (gift wrapping) algorithm." << endl;
        ConvexHullJarvis();
        cout << "Convex hull is created." << endl;
        cout << "Now, what do you want to do?" << endl;
        cout << "Press 0 to exit." << endl;
        cout << "Press any key to return to home." << endl;
        getline(cin, opt);
        if(opt=="0") exit(EXIT_SUCCESS);
        else
        {
            cout << endl;
            Home();
        }
    }
    else if(opt=="2")
    {
        cout << endl << "You chose the Graham's scan algorithm." << endl;
        ConvexHullGraham();
        cout << "Convex hull is created." << endl;
        cout << "Now, what do you want to do?" << endl;
        cout << "Press 0 to exit." << endl;
        cout << "Press any key to return to home." << endl;
        getline(cin, opt);
        if(opt=="0") exit(EXIT_SUCCESS);
        else
        {
            cout << endl;
            Home();
        }
    }
    else
    {
        cerr << endl << "ERROR:" << endl;
        cout << "There is no method option like this!" << endl;
        cout << "Now, what am i going to do with you?" << endl;
        Home();
    }
}

void ConvexHullJarvis()
{
    vector <Point> cset, *pset, outset;
    vector <Polygon> polset;
    Point start, turn, prev, next;
    Polygon pol(cset);
    BasicIO input, output;
    GeomImage graph;

    input.setFile("Points.txt");
    input.readFile();
    input.read2Vector(cset);

    //Find the Left Most (Start) and the Right Most (Turn) Points
    start=cset[0];
    turn=cset[0];
    for(unsigned int i=0; i<cset.size(); i++)
    {
        if(cset[i].getX() < start.getX()) start=cset[i];
        if(cset[i].getX() > turn.getX()) turn=cset[i];
    }

    graph.setFileName("Jarvis' March Convex Hull.bmp");
    graph.drawPointsOnCanvas(cset, RED);

    //Add the Start (Also the End) Point of Polygon
    bool flame=false;
    pset=&cset;
    prev=start;
    pol.addPoint(start);
    next=prev.findNext(prev, *pset, flame);
    pol.addPoint(next);
    prev=next;
    if(next.isSame(turn)) flame=true;
    cset.push_back(start);

    //Find, Connect and Add the Corner Points of Polygon
    unsigned int k=cset.size();
    for(unsigned int i=0; i<k; i++)
    {
        next=prev.findNext(prev,*pset, flame);
        pol.addPoint(next);
        if(next.isSame(start)) break;
        else prev=next;
        if(next.isSame(turn)) flame=true;
    }

    output.setFile("Jarvis' Polygon.txt");
    for(int i=0; i<pol.getNumOfPoints(); i++)
    {
        outset.push_back(pol.getPoint(i));
    }
    output.getFromVector(outset);
    output.writeFile();

    polset.push_back(pol);
    graph.drawPolygonsOnCanvas(polset, BLUE);
    graph.writeBMP();
}

void ConvexHullGraham()
{
    vector <Point> cset, *pset, outset;
    vector <Polygon> polset;
    Point start, turn, prev, next;
    Polygon pol(outset);
    BasicIO input, output;
    GeomImage graph;

    input.setFile("Points.txt");
    input.readFile();
    input.read2Vector(cset);

    //Find the Lowest (Start) Point
    start=cset[0];
    for(unsigned int i=0; i<=cset.size(); i++)
    {
        if(cset[i].getY()<start.getY()) start=cset[i];
    }
    o=start;

    graph.setFileName("Graham's Scan Convex Hull.bmp");
    graph.drawPointsOnCanvas(cset, RED);
    graph.writeBMP();

    cset.push_back(start);
    sort(cset.begin(), cset.end(), compAngle);
    cset.push_back(start);
    pset=&cset;
    pol.setPoints(*pset);

    //Find the CCW Turning Points
    for(int i=1; i<(pol.getNumOfPoints()-1); i++)
    {
        if(pol.getPoint(i).isSame(start)) break;
        else if(!(pol.getPoint(i).isCCW(pol.getPoint(i-1), pol.getPoint(i+1))))
        {
            pol.delPoint(i);
            i--;
        }
    }

    //Rescan to Correct Errors and Find the Polygon
    bool error=true;
    while(error)
    {
        error=false;
        for(int i=1; i<(pol.getNumOfPoints()-1); i++)
        {
            if((pol.getPoint(i).isSame(start))||(!(pol.getPoint(i).isCCW(pol.getPoint(i-1),pol.getPoint(i+1)))))
            {
                error=true;
                pol.delPoint(i);
                i--;
            }
        }
    }

    output.setFile("Graham's Polygon.txt");
    for(int i=0; i<pol.getNumOfPoints(); i++)
    {
        outset.push_back(pol.getPoint(i));
    }
    output.getFromVector(outset);
    output.writeFile();

    polset.push_back(pol);
    graph.drawPolygonsOnCanvas(polset, BLUE);
    graph.writeBMP();
}

bool compAngle(Point p, Point q)
{
    float a=p.polAngle(o);
    float b=q.polAngle(o);
    if(a<b) return true;
    else return false;
}
