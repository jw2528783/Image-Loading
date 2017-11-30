#include <stdio.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include "Image.h"
#include "Frame.h"

extern Frame frame;

void Image::load(const char * filename, int w, int h) {
	this->w = w;
	this->h = h;
	pixels = new byte[w * h * 3];

	std::stringstream ss;

	ss << "ffmpeg -i " << filename <<
	" -f rawvideo -pix_fmt rgb24 " <<
	"-vf scale=" << w << ":" << h <<
	" - ";

	FILE * pipe = popen(ss.str().c_str(), "r");

	fread(pixels, 3, w * h, pipe);
	fclose(pipe);
}

void Image::draw() const {
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			byte r = pixels[i * w * 3 + j * 3 + 0];
			byte g = pixels[i * w * 3 + j * 3 + 1];
			byte b = pixels[i * w * 3 + j * 3 + 2];
			frame.setPixel(x + 0.5 + j, y + 0.5 + i, r, g, b);
		}
	}
}

void Image::setVelocity(double xvel, double yvel) {
	this->xvel = xvel;
	this->yvel = yvel;
}

void Image::update(double time) {
	x = x + xvel;
	y = y + yvel;
}
