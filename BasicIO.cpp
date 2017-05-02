#include "BasicIO.h"
#include <iostream>
#include <fstream>
using namespace std;
BasicIO::BasicIO(){
    pointSet.clear();
}

void BasicIO::setFile(char* fN){
    fileName = fN;
}

void BasicIO::readFile(){
    int x,y;
    ifstream infile;
    infile.open (fileName);
    while(!infile.eof()){
        infile>>x;
        infile>>y;
        pointSet.push_back(Point(x,y));
    }
    infile.close();
}
void BasicIO::writeFile(){
    ofstream outfile;
    outfile.open(fileName);
    for(unsigned int i=0;i<pointSet.size();i++)
        outfile<<pointSet[i].getX()<<" "<<pointSet[i].getY()<<endl;

}
//Copy the values read from file to a point vector
void BasicIO::read2Vector(std::vector<Point>& pntSet){
    for(unsigned int i=0;i<pointSet.size();i++)
        pntSet.push_back(pointSet[i]);
}
//Copy the values from point vector to the file writer
void BasicIO::getFromVector(std::vector<Point>& pntSet){
    for(unsigned int i=0;i<pntSet.size();i++)
        pointSet.push_back(pntSet[i]);
}
