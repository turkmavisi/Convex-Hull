#include "GeomImage.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

GeomImage::GeomImage(){
	//Create White Canvas
	red = new int[640*480];
	green = new int[640*480];
	blue = new int[640*480];

	memset(red,255,sizeof(int)*640*480);
	memset(green,255,sizeof(int)*640*480);
	memset(blue,255,sizeof(int)*640*480);
}

GeomImage::~GeomImage(){
	delete [] red ;
	delete [] green;
	delete [] blue;

}

//Filename for output
void GeomImage::setFileName(char* fName){
	fileName = fName;
}

void GeomImage::put(int x,int y,COLOR clr){
		switch(clr){
			case RED:
				red[x+y*640]=255;
				green[x+y*640]=0;
				blue[x+y*640]=0;
				break;
			case GREEN:
				red[x+y*640]=0;
				green[x+y*640]=255;
				blue[x+y*640]=0;
				break;
			case BLUE:
				red[x+y*640]=0;
				green[x+y*640]=0;
				blue[x+y*640]=255;
				break;

		}
}

void GeomImage::drawLine(Point p1,Point p2,COLOR clr){
	//Implementation of Bresenham's line algorithm
	int x0=p1.getX();
	int y0=p1.getY();

	int x1=p2.getX();
	int y1=p2.getY();

        bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep){
		std::swap(x0,y0);
		std::swap(x1,y1);
	}

	if (x0 > x1) {
		std::swap(x0,x1);
		std::swap(y0,y1);
	}

	int dX = (x1 - x0), dY = abs(y1 - y0), err = (dX / 2), ystep = (y0 < y1 ? 1 : -1), y = y0;

	for (int x = x0; x <= x1; ++x)
	{
		if(steep)
			put(y,x,clr);
		else
			put(x,y,clr);
		err = err - dY;
		if (err < 0){
			y += ystep;
			err += dX;
		}
	}

}
void GeomImage::drawPointsOnCanvas(std::vector<Point> pntSet,COLOR clr){
	int dx[] = {-1,-1,-1,0,0,0,1,1,1};
	int dy[] = {-1,0,1,-1,0,1,-1,0,1};
	for(unsigned int i=0;i<pntSet.size();i++){
		if((pntSet[i].getX()<0)||(pntSet[i].getY()<0)||(pntSet[i].getY()>=479)||(pntSet[i].getX()>=639))
			std::cerr<<"Point "<<i<<"is out of bounds(W:640,H:480)"<<std::endl;
		for(int j=0;j<9;j++)
            if(!((pntSet[i].getX()+dx[j]<0)||(pntSet[i].getY()+dy[j]<0)||(pntSet[i].getY()+dy[j]>=479)||(pntSet[i].getX()+dx[j]>=639)))
                put(pntSet[i].getX()+dx[j],pntSet[i].getY()+dy[j],clr);
	}
}

void GeomImage::drawLinesOnCanvas(std::vector<Line> lnSet,COLOR clr){
	for(unsigned int i=0;i<lnSet.size();i++)
		drawLine(lnSet[i].getP1(),lnSet[i].getP2(),clr);
}

void GeomImage::drawPolygonsOnCanvas(std::vector<Polygon> plySet,COLOR clr){
    for(unsigned int i=0;i<plySet.size();i++){
        for(int j=0;j<plySet[i].getNumOfPoints()-1;j++)
        {
            this->drawLine(plySet[i].getPoint(j),plySet[i].getPoint(j+1),clr);
        }
        this->drawLine(plySet[i].getPoint(plySet[i].getNumOfPoints()-1),plySet[i].getPoint(0),clr);
    }

}


void GeomImage::writeBMP(){
	//Prepare the header file and write to the .bmp
	unsigned char *img = NULL;
	int w = 640;
	int h = 480;
	int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int, 54 is header size
	if( img )
    		free( img );
	img = (unsigned char *)malloc(3*w*h);
	memset(img,0,sizeof(unsigned char)*w*h*3); //memset is the most efficient way to

	int x,yres,r,g,b,y;

	yres =h;
	for(int i=0; i<640; i++)
	{
        for(int j=0; j<480; j++)
		{
		    x=i; y=(yres-1)-j;
		    r = red[i+j*640];
		    g = green[i+j*640];
		    b = blue[i+j*640];
		    if (r > 255) r=255;
		    if (g > 255) g=255;
		    if (b > 255) b=255;
		    img[(x+y*w)*3+2] = (unsigned char)(r);
		    img[(x+y*w)*3+1] = (unsigned char)(g);
		    img[(x+y*w)*3+0] = (unsigned char)(b);
		}
	}
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	FILE* f = fopen(fileName,"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<h; i++)
	{
	    fwrite(img+(w*(h-i-1)*3),3,w,f);
	    fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	fclose(f);
}
