CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
LIBRARIES:= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
.PHONY: all clean
all: example_-1
example_-1:
	$(CC) $(CFLAGS) -o example_-1 example_-1.cpp $(LIBRARIES)

clean:
	rm -f *.o
