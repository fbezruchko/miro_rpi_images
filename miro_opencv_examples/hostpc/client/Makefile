CC:= g++
CFLAGS:= -I/usr/local/include/opencv4 -L/usr/local/lib -std=c++11
OBJECTS:=
LIBRARIES:= -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_flann -lopencv_imgcodecs -lopencv_video -lopencv_videoio -lopencv_objdetect
.PHONY: all clean
all: client
client:
	$(CC) $(CFLAGS) -o client client.cpp $(LIBRARIES)

clean:
	rm -f *.o
