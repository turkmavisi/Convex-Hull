#ifndef _BASICIO_H
#define _BASICIO_H
#include <vector>
#include "Point.h"
class BasicIO{
private:
    char *fileName;
    std::vector<Point> pointSet;
public:
    BasicIO();
    void setFile(char* fN);
    void readFile();
    void writeFile();

    void read2Vector(std::vector<Point>& pntSet);
    void getFromVector(std::vector<Point>& pntSet);
};
#endif
