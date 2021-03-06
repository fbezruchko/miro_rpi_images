#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
using namespace cv;

Mat MATframe;

void drawRectangle(int x, int y)
{
	Mat copy = MATframe;
	Vec3b color = copy.at<Vec3b>(Point(x, y));
	rectangle(copy, Point(copy.rows - 50, 0), Point(copy.rows, 50), Scalar(color), -1);
	printf("%d x %d (BGR): [ %d, %d, %d]\n", x, y, color[0], color[1], color[2]);

	int sock;
        struct sockaddr_in addr;

        char msg1[] = "Hello there!";

        sock = socket(AF_INET, SOCK_DGRAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(4001);
        addr.sin_addr.s_addr = inet_addr("192.168.1.214");
	connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	send(sock, &color, sizeof(color), 0);
	//send(sock, msg1, sizeof(msg1), 0);
	//sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	close(sock);
}

void myMouseCallback(int event, int x, int y, int flags, void* param)
{
	switch (event) {
	case EVENT_MOUSEMOVE:
		break;

	case EVENT_LBUTTONDOWN:
		drawRectangle(x, y);
		break;

	case EVENT_LBUTTONUP:
		break;
	}
}

int main(int argc, char* argv[])
{
	const char* gst = "udpsrc port=4000 ! application/x-rtp,media=(string)video,encoding-name=(string)JPEG ! rtpjpegdepay ! decodebin ! videoconvert ! appsink";
	cv::VideoCapture capture(gst, CAP_GSTREAMER);
	cout<<"Example 6. OpenCV + Events on HOST-PC + Sockets"<<endl;
	if (!capture.isOpened()) {cerr<<"Error opening the stream"<<endl;return -1;}

	cout<<"Capture is opened!"<<endl;

	cv::namedWindow("RPiCameraStream", WINDOW_AUTOSIZE);
	setMouseCallback("RPiCameraStream", myMouseCallback);

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

		usleep(10000);
	}
	capture.release();
	destroyWindow("RPiCameraStream");

	return 0;
}
