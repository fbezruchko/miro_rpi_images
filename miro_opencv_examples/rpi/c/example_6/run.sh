./example_6 | gst-launch-1.0 fdsrc ! "image/jpeg,framerate=40/1" ! jpegparse ! rtpjpegpay ! udpsink host=192.168.1.133 port=4000
