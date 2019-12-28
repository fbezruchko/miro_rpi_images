CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
LIBRARIES:= -lpthread -lraspicam -lraspicam_cv -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
.PHONY: all clean
all: example_6
example_6:
	$(CC) $(CFLAGS) -o example_6 example_6.cpp $(LIBRARIES)

clean:
	rm -f *.o
