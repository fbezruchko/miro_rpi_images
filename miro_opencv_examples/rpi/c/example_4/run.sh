./example_4 | gst-launch-1.0 fdsrc ! "image/jpeg,framerate=40/1" ! jpegparse ! rtpjpegpay ! udpsink host=192.168.0.106 port=4000

