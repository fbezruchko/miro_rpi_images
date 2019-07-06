CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
LIBRARIES:= -lpthread -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_imgcodecs -lopencv_video -lopencv_videoio -lopencv_ml -lopencv_objdetect
.PHONY: all clean
all: opencv_worker

opencv_worker:
	$(CC) $(CFLAGS) -o opencv_worker opencv_worker.cpp $(LIBRARIES)

clean:
	rm -f *.o
