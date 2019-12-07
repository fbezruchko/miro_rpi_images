CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
#LIBRARIES:= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_imgcodecs -lopencv_video -lopencv_videoio -lopencv_ml -lopencv_objdetect
LIBRARIES:= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
.PHONY: all clean
all: example_1
example_1:
	$(CC) $(CFLAGS) -o example_1 example_1.cpp $(LIBRARIES)

clean:
	rm -f *.o
