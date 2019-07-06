// Required defines
#define MULTIPART_STREAM_BOUNDARY "--FRAME_START" // Custom boundary defined in the multipart stream from stdin
#define MULTIPART_STREAM_BOUNDARY_SIZE 13
 
// Includes
#include <iostream>
#include <string>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <opencv2/opencv.hpp> // openCV C++ header
 
using namespace std;
using namespace cv;
 
// Global variables
// Input JPEG frame
char* inputJPEGFrame=NULL;
size_t inputJPEGFrameSize=0;
pthread_mutex_t inputJPEGFrameMutex=PTHREAD_MUTEX_INITIALIZER;
// Output JPEG frame
char* outputJPEGFrame=NULL;
size_t outputJPEGFrameSize=0;
bool outputJPEGFrameUpdated=false;
pthread_mutex_t outputJPEGFrameMutex=PTHREAD_MUTEX_INITIALIZER;
 
// Fill zero to array
void arrayFillZeros(char* array, size_t arraySize) {
 for(size_t i=0; i<=arraySize-1; i++) {
  array[i]='\0';
 }
}
 
// Push back character into array
void arrayPushCharAtBack(char array[], size_t arraySize, char c) {
 size_t i;
 for(i=0; i<=arraySize-3; i++) { // -3: 1 for "<=", 1 for c, 1 for \0
  array[i]=array[i+1];
 }
 array[i]=c;
 array[++i]='\0';
}
 
// Frame processing thread
void *frameProcessingThread(void* arg) {
 // Solve the issue when inputJPEGFrameSize=0, openCV fails
 while(true) {
  pthread_mutex_lock(&inputJPEGFrameMutex);
  if(inputJPEGFrameSize > 0) {
   pthread_mutex_unlock(&inputJPEGFrameMutex);
   break;
  }
  pthread_mutex_unlock(&inputJPEGFrameMutex);
 }
  
 // Main processing loop
 while(true) {
  // Obtain a local copy of input frame first
  pthread_mutex_lock(&inputJPEGFrameMutex);
  unsigned char* processingFrame=(unsigned char*)malloc(sizeof(unsigned char)*inputJPEGFrameSize);
  memcpy(processingFrame, inputJPEGFrame, inputJPEGFrameSize);
  size_t processingFrameSize=inputJPEGFrameSize;
  pthread_mutex_unlock(&inputJPEGFrameMutex); // Release to main thread while we process this frame here
   
  // Do our processing to processingFrame here, remember to update processingFrameSize
   
  // JPEG to Mat
  //Mat rawJPEG = Mat(1, processingFrameSize, CV_8UC3, processingFrame);
  Mat imgBuf = Mat(1, processingFrameSize, CV_8UC3, processingFrame);
  Mat imgMat = imdecode(imgBuf, CV_LOAD_IMAGE_COLOR);
  free(processingFrame);
  if(imgMat.data == NULL) {
   cout << "Error when decoding JPEG frame for openCV." << endl;
   exit(-1);
  }
     
  // Process imgMat here
   
  // Mat to JPEG
  vector<uchar> buf;
  imencode(".jpg", imgMat, buf, std::vector<int>());
  processingFrame=(unsigned char*)malloc(buf.size());
  memcpy(processingFrame, &buf[0], buf.size());
  processingFrameSize=buf.size();
   
  // Output the processed frame for output
  pthread_mutex_lock(&outputJPEGFrameMutex);
  free(outputJPEGFrame);
  outputJPEGFrame=(char*)malloc(sizeof(char)*processingFrameSize);
  memcpy(outputJPEGFrame, processingFrame, processingFrameSize);
  outputJPEGFrameSize=processingFrameSize;
  outputJPEGFrameUpdated=true;
  pthread_mutex_unlock(&outputJPEGFrameMutex);
   
  // Clean up, avoid evil memory leaks plz
  free(processingFrame);
 }
 return NULL;
}
 
void *frameOutputThread(void* arg) {
 while(true) {
  pthread_mutex_lock(&outputJPEGFrameMutex);
  if(outputJPEGFrameUpdated) {
   write(STDOUT_FILENO, outputJPEGFrame, outputJPEGFrameSize);
   outputJPEGFrameUpdated=false;
  }
  pthread_mutex_unlock(&outputJPEGFrameMutex);
  usleep(2000);
 }
 return NULL;
}
 
int main(int argc, char** argv) {
 if(argc == 1) {
  // Thread creation
  pthread_t frame_processing_thread, frame_output_thread;
  pthread_create(&frame_processing_thread, NULL, frameProcessingThread, NULL);
  pthread_create(&frame_output_thread, NULL, frameOutputThread, NULL);
  usleep(3000); // Dumb method to wait thread up, just hope it doesn't add much delay to the stream, and the thread have the time to finish intiialization
   
  // Read stdin
  size_t bytesRead=0;
  char byteBuffer[1]={0x00};
  char boundaryKeywordWindow[MULTIPART_STREAM_BOUNDARY_SIZE+1]; // +1 for \0
  char contentLengthKeywordWindow[16+1]; // "Content-Length: " is 16 in length, +1 for \0
  char contentLength[8]; // 8 bytes (7 bytes long) should be enough for content length, 1280*720*3=2764800(Not JPEG compressed), only 7 bytes long
  arrayFillZeros(boundaryKeywordWindow, MULTIPART_STREAM_BOUNDARY_SIZE+1);
  arrayFillZeros(contentLengthKeywordWindow, 16+1);
  while(true) { // Main while loop
   // 1: Locate boundary keyword [This one could be removed]
   /*while(true) {
    bytesRead=read(STDIN_FILENO, byteBuffer, 1);
    if(bytesRead == 1) {
     arrayPushCharAtBack(boundaryKeywordWindow, MULTIPART_STREAM_BOUNDARY_SIZE+1, byteBuffer[0]);
     //arrayDump(boundaryKeywordWindow, MULTIPART_STREAM_BOUNDARY_SIZE+1);
    }
    if(bytesRead < 0) { // error
     cout << "Error when reading from stdin." << endl;
     exit(-1);
    }
    if(strcmp(boundaryKeywordWindow, MULTIPART_STREAM_BOUNDARY) == 0) {
     break;
    }
   }*/ // Removed to reduce delay
   // 2: Locate "Content-Length: "
   while(true) {
    bytesRead=read(STDIN_FILENO, byteBuffer, 1);
    if(bytesRead == 1) {
     arrayPushCharAtBack(contentLengthKeywordWindow, 16+1, byteBuffer[0]);
    }
    if(bytesRead < 0) { // error
     cout << "Error when reading from stdin." << endl;
     exit(-1);
    }
    if(strcmp(contentLengthKeywordWindow, "Content-Length: ") == 0) {
     break;
    }
   }
   // 3: Extract content length of the current frame
   size_t i=0;
   while(true) {
    bytesRead=read(STDIN_FILENO, byteBuffer, 1);
    if(bytesRead == 1) {
     if(byteBuffer[0] != 0x0D) {
      contentLength[i]=byteBuffer[0];
      i++;
     }else{
      contentLength[i]=0x00; // \0
      break;
     }
    }
    if(bytesRead < 0) { // error
     cout << "Error when reading from stdin." << endl;
     exit(-1);
    }
   }
   // 4: Skip the following 3 bytes (0x0A, 0x0D, 0x0A)
   for(i=0; i<=2; i++) {
    bytesRead=read(STDIN_FILENO, byteBuffer, 1);
    if(bytesRead < 0) { // error
     cout << "Error when reading from stdin." << endl;
     exit(-1);
    }
   }
   // 5: Extract JPEG frame
   ssize_t jpegBytes=atoi(contentLength);
   pthread_mutex_lock(&inputJPEGFrameMutex);
   free(inputJPEGFrame);
   inputJPEGFrame=(char*)malloc(sizeof(char)*jpegBytes);
   inputJPEGFrameSize=jpegBytes;
   if(read(STDIN_FILENO, inputJPEGFrame, jpegBytes) != jpegBytes) { // Incomplete read, or error
    cout << "Error, jpeg frame incomplete" << endl;
    free(inputJPEGFrame);
    pthread_mutex_unlock(&inputJPEGFrameMutex);
    exit(-1);
   }else{
    pthread_mutex_unlock(&inputJPEGFrameMutex);
   }
  }
 }else{
  // argc != 1
  // Error handling?
 }
}
