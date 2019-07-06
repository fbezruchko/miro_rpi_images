#include <iostream>
#include <string>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    const char* gst = "udpsrc port=4000 ! "
		    "\""
		    "application/x-rtp,media=(string)video,clock-rate=(int)90000,encoding-name=(string)JPEG,a-framerate=(string)40.000000,a-framesize=(string)640-480,payload=(int)26"
		    "\""
		    " ! rtpjpegdepay ! decodebin ! autovideosink";

    cv::VideoCapture capture(gst);

    if (!capture.open()) {cerr<<"Error opening the stream"<<endl;return -1;}
    
    Mat MATframe;
    cv::namedWindow("RPiCameraStream", CV_WINDOW_AUTOSIZE);

    while (true)
    {
	// Получаем кадр
	if (!capture.read(MATframe))
	{
		std::cout<<"Capture read error"<<std::endl;
		break;
	}
	else
	{
		cv::imshow("RPiCameraStream", MATframe);
		cv::waitKey(1);
	}
    }
    // Освобождаем ресурсы
    capture.release();
    return 0;
}
