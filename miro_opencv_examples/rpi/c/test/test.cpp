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
// имя картинки
string filename = "Image0.jpg";
// получаем картинку
image = imread(filename, IMREAD_COLOR);
// окно для отображения картинки
//namedWindow("original", WINDOW_AUTOSIZE);
// показываем картинку
//imshow("original", image);
// выводим в консоль информацию о картинке
printf("[i] image: %s\n", filename);
printf("[i] channels: %i\n", image.channels());
printf("[i] width: %i pixels\n", image.rows);
printf("[i] height: %i pixels\n", image.cols);
// ждём нажатия клавиши
//waitKey(0);
// удаляем окно
//destroyWindow("original");
return 0;
}
