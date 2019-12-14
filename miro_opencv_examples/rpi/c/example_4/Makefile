CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
LIBRARIES:= -lraspicam -lraspicam_cv -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_objdetect
.PHONY: all clean
all: example_4
example_4:
	$(CC) $(CFLAGS) -o example_4 example_4.cpp $(LIBRARIES)

clean:
	rm -f *.o
