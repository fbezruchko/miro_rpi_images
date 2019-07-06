CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
LIBRARIES:= -lraspicam -lraspicam_cv -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_imgcodecs -lopencv_video -lopencv_videoio -lopencv_ml -lopencv_objdetect
.PHONY: all clean
all: video_capture_opencv_raspicam_canny
video_capture_opencv_raspicam_canny:
	$(CC) $(CFLAGS) -o video_capture_opencv_raspicam_canny video_capture_opencv_raspicam_canny.cpp $(LIBRARIES)

clean:
	rm -f *.o
