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
    const char* gst = "udpsrc port=4000 ! application/x-rtp,media=(string)video,encoding-name=(string)JPEG ! rtpjpegdepay ! decodebin ! videoconvert ! appsink";

    cv::VideoCapture capture(gst, CAP_GSTREAMER);
    cout<<"Try open capture..."<<endl;

    if (!capture.isOpened()) {cerr<<"Error opening the stream"<<endl;return -1;}
    cout<<"Capture is opened!"<<endl;

    Mat MATframe;
    //cv::namedWindow("RPiCameraStream", CV_WINDOW_AUTOSIZE);

    while (true)
    {
        capture.read(MATframe);
	if (MATframe.empty())
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
    capture.release();
    destroyWindow("RPiCameraStream");
    
    return 0;
}
