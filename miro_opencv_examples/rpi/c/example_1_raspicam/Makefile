CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
LIBRARIES:= -lraspicam -lraspicam_cv -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
.PHONY: all clean
all: example_1_raspicam
example_1_raspicam:
	$(CC) $(CFLAGS) -o example_1_raspicam example_1_raspicam.cpp $(LIBRARIES)

clean:
	rm -f *.o
