#include "rectangle.h"
#include "Frame.h"

typedef unsigned char byte;

extern Frame frame;

void Rectangle::setx(double newx) {
	x = newx;
}

void Rectangle::sety(double newy) {
	y = newy;
}

void Rectangle::update(double dt) {
	x = x + dx;
	y = y + dy;

}

void Rectangle::setVelocity(double dx, double dy) {
	this->dx = dx;
	this->dy = dy;
}

void Rectangle::draw() const {
	for(int i = 0; i < h; ++i) {
		for(int j = 0; j < w; ++j) {
			frame.setPixel(x + 0.5 + j, y + 0.5 + i, r, g, b);
		}
	}

}

void Rectangle::setColor(byte red, byte green, byte blue) {
	r = red;
	g = green;
	b = blue;
}
