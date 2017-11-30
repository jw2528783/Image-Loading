#pragma once
#include <sstream>
typedef unsigned char byte;

class Image {
public:
	Image() : pixels(0), w(0), h(0),x(0),y(0),xvel(0),yvel(0) {}
	~Image(){delete [] pixels;}	
	void load(const char * filename, int w, int h);
	void draw() const;
	void update(double dt);
	void setx(int xvalue){x=xvalue;}
	void sety(int yvalue){y=yvalue;}
	void setVelocity(double xvel, double yvel);

private:
	byte * pixels;
	int w;
	int h;
	int x;
	int y;
	double xvel;
	double yvel;
};
