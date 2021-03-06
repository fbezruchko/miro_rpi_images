#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	raspicam::RaspiCam_Cv capture;
	capture.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if (!capture.open()) {cerr<<"Error opening the camera"<<endl; return -1;}

	Mat MATframe;
	usleep(1000000);
	
	while (true)
	{
		capture.grab();
		capture.retrieve(MATframe);
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
