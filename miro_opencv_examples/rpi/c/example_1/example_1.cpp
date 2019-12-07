#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	VideoCapture capture = VideoCapture(0);
	if (!capture.isOpened()) return -1;

	capture.set(CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CAP_PROP_FRAME_HEIGHT, 480);

	Mat MATframe;
	usleep(1000000);
	
	while (true)
	{
		capture >> MATframe;
		flip(MATframe, MATframe, 0);
		
		// Mat to JPEG
		vector<uchar> buf;
		imencode(".jpg", MATframe, buf, std::vector<int>());
		write(STDOUT_FILENO, buf.data(), buf.size());

		usleep(30000);
	}
	capture.release();

	return 0;
}
