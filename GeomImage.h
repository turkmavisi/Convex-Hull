#ifndef _GEOM_IMAGE
#define _GEOM_IMAGE

#define W 640;
#define H 480;

#include <vector>
#include "Point.h"
#include "Line.h"
#include "Polygon.h"
enum COLOR{RED,GREEN,BLUE};

class GeomImage{
	private:
		char * fileName;
		int *red;
		int *green;
		int *blue;
		void drawLine(Point p1,Point p2,COLOR clr);
		void put(int x,int y,COLOR clr); //Put a point on canvas
	public:
		GeomImage();
		~GeomImage();
		void setFileName(char* fName);
		void drawPointsOnCanvas(std::vector<Point> pntSet,COLOR clr);
		void drawLinesOnCanvas(std::vector<Line> lnSet,COLOR clr);
		void drawPolygonsOnCanvas(std::vector<Polygon> plySet,COLOR clr);
		void writeBMP();
};

#endif