#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat image;

int main(int argc, char* argv[])
{
	string filename = "Khabarovsk.jpg";
	printf("[i] image: %s\n", filename.c_str());
	image = imread(filename, IMREAD_COLOR);
	printf("[i] channels: %i\n", image.channels());
	printf("[i] width: %i pixels\n", image.rows);
	printf("[i] height: %i pixels\n", image.cols);
	return 0;
}
