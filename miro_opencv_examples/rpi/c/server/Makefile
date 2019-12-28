CC:= g++
CFLAGS:= -I/usr/local/include/opencv -L/usr/local/lib
OBJECTS:=
LIBRARIES:= -lraspicam -lraspicam_cv -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
.PHONY: all clean
all: server
server:
	$(CC) $(CFLAGS) -o server server.cpp $(LIBRARIES)

clean:
	rm -f *.o
