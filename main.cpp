#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include "Frame.h"
#include "Image.h"
#include "rectangle.h"
typedef unsigned char byte;
using namespace std;

const double frames_per_second = 60; 
const int duration_in_seconds = 3;
Frame frame(720, 480);

int main(int argc, char * argv[]) {
	// Construct the ffmpeg command to run.
	const char * cmd = 
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

	// Run the ffmpeg command and get pipe to write into its standard input stream.

	FILE * pipe = popen(cmd, "w");

	if (pipe == 0) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}
	Rectangle rec(30,30);
	Rectangle rec2(60,60);
	Image image;
	Image image2;
	rec.setx(300);
	rec.sety(400);
	rec2.setx(600);
	rec2.sety(0);
	image.setx(5);
	image.sety(20);
	image2.setx(200);
	image2.sety(200);
	rec.setVelocity(5,0);
	rec2.setVelocity(0,5);
	image.setVelocity(0,2);
	image2.setVelocity(3,1);
	rec.setColor(0x00, 0x00, 0xFF);
	rec.setColor(0xFF, 0x00, 0x00);
	image.load("ducky.bmp", 150, 150);
	image2.load("tux.bmp",100,100);

	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double time=i/frames_per_second;

		frame.clear();
		rec.draw();
		rec2.draw();
		image.draw();
		image2.draw();
		rec.update(time);
		rec2.update(time);
		image2.update(time);
		image.update(time);
		
		frame.write(pipe);
	}

	fflush(pipe);
#ifdef _WIN32
	_pclose(pipe);
#else
	pclose(pipe);
#endif

	cout << "\nnum_frames: " << num_frames << endl<<endl;
	cout << "\nDone.\n" << endl;

	return 0;
}
