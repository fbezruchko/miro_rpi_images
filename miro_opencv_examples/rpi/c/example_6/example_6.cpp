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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

using namespace std;
using namespace cv;

void* thread_recv_data_func(void *args)
{
	int sock;
	struct sockaddr_in addr;
	char sock_buf[1024];
	int sock_bytes_read;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4001);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

	FILE *pFile;
	Vec3b color;
	while(1)
	{
	    sock_bytes_read = recvfrom(sock, sock_buf, 1024, 0, NULL, NULL);
	    color = *((Vec3b*)sock_buf);
	    pFile = fopen("out.txt", "a+t");
	    fprintf(pFile, "BGR: [%d, %d, %d]\n", color[0], color[1], color[2]);
	
	    fclose(pFile);
	    usleep(10000);
	}
}

int main(int argc, char* argv[])
{
	pthread_t thread_recv_data;
	if(pthread_create(&thread_recv_data, NULL, thread_recv_data_func, NULL))
	{
		printf("Can't create thread!\n");
		return -1;	
	}

	raspicam::RaspiCam_Cv capture;
	capture.set(CV_CAP_PROP_FORMAT, CV_8UC3);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if (!capture.open()) {cerr<<"Error opening the camera"<<endl; return -1;}

//	cv::VideoWriter writer;
//	writer.open("appsrc ! \"image/jpeg,framerate=40/1\" ! jpegparse ! rtpjpegpay ! udpsink host=192.168.1.214 port=4000", 0, 30.0, cv::Size(640, 480), true);
//	writer.open("appsrc ! x264enc ! mpegtsmux ! udpsink host=192.168.1.214 port=4000", 0, 30.0, cv::Size(640, 480), true);

//	if (!writer.isOpened())
//	{
//		cerr<<"Error opening writer"<<endl; 
//		return -1;
//	}

	Mat MATframe;
	Vec3b color;

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
		usleep(10000);
	}
	capture.release();
	
	pthread_cancel(thread_recv_data);

	return 0;
}
