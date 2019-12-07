gst-launch-1.0 udpsrc port=4000 ! "application/x-rtp,media=(string)video,clock-rate=(int)90000,encoding-name=(string)JPEG" ! rtpjpegdepay ! decodebin ! autovideosink
