#include <iostream>
#include <string>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

using namespace std;
using namespace cv;

int lowThreshold = 50;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;

int main(int argc, char* argv[])
{
	raspicam::RaspiCam_Cv capture;
	// Можно вручную задать разрешение
	capture.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	
	if (!capture.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
	
	Mat MATframe, MATframe_gray, CANNYframe, EDGESframe;
	usleep(1000000);
	while (true)
	{
		// Получаем кадр
		capture.grab();
		capture.retrieve(MATframe);
		flip(MATframe, MATframe, 0);
		
		CANNYframe.create(MATframe.size(), MATframe.type());
		cvtColor(MATframe, MATframe_gray, COLOR_BGR2GRAY);
		blur(MATframe_gray, EDGESframe, Size(3,3));
		Canny(EDGESframe, EDGESframe, lowThreshold, lowThreshold*ratio, kernel_size);
		CANNYframe = Scalar::all(0);
		MATframe.copyTo(CANNYframe, EDGESframe);
		cvtColor(EDGESframe, EDGESframe, CV_GRAY2BGR);

		// Mat to JPEG
		vector<uchar> buf;

		//imencode(".jpg", EDGESframe, buf, std::vector<int>());
		imencode(".jpg", CANNYframe, buf, std::vector<int>());

		unsigned char* JPEGframe=(unsigned char*)malloc(buf.size());
		memcpy(JPEGframe, &buf[0], buf.size());
		write(STDOUT_FILENO, JPEGframe, buf.size());
		free(JPEGframe);

		usleep(10000);
	}
	// Освобождаем ресурсы
	capture.release();
	return 0;
}

