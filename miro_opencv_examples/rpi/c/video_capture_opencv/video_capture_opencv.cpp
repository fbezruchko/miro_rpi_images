#include <iostream>
#include <string>
#include <unistd.h>
//#include <pthread.h>
//#include <time.h>

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
	// Получаем любую подключённую камеру
	VideoCapture capture = VideoCapture(0);
	if (!capture.isOpened()) return -1;
	// Можно вручную задать разрешение
	capture.set(CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CAP_PROP_FRAME_HEIGHT, 480);
	//capture.set(CAP_PROP_AUTO_EXPOSURE, 0.25); 
	//capture.set(CV_CAP_PROP_EXPOSURE, -7);

	//namedWindow("capture", WINDOW_AUTOSIZE);
	//printf("[i] press Enter for capture image and Esc for quit!\n\n");
	//int counter = 0;
	//char filename[512];

	Mat MATframe;
	usleep(1000000);
	while (true)
	{
		// Получаем кадр
		capture >> MATframe;
		flip(MATframe, MATframe, 0);
		
		// Mat to JPEG
		vector<uchar> buf;
		imencode(".jpg", MATframe, buf, std::vector<int>());
		unsigned char* JPEGframe=(unsigned char*)malloc(buf.size());
		memcpy(JPEGframe, &buf[0], buf.size());
		write(STDOUT_FILENO, JPEGframe, buf.size());
		free(JPEGframe);

		usleep(30000);

		// Отображаем кадр
		//imshow("capture", frame);
		//char c = waitKey(33);
		//if (c == 27) // нажата ESC
		//{
		//	break;
		//}
		//else if (c == 13) // нажата Enter
		//{
			// Сохраняем кадр в файл
		//	sprintf(filename, "Image%d.jpg", counter);
		//	printf("[i] capture... %s\n", filename);
		//	imwrite(filename, frame);
		//	counter++;
		//}
	}
	// Освобождаем ресурсы
	capture.release();
	//destroyWindow("capture");
	return 0;
}

