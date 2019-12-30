# Raspberry Pi Images for Miro robotic platform
This is a special images for Raspberry Pi boards, installed in Miro robot.

# Download
https://drive.google.com/open?id=1bLlsLpjBi-Di4cmWVUgB6gK2bqHcH0PD

https://drive.google.com/open?id=14F3dctxI-pH9pbUo_ci-mFrzzorWOyUk

# Content
"raspbian_stretch_kinetic_ocv346_rpizero.img" - Image based on Raspbian lite (April, 2019) with ROS Kinetic (ros-comm), gstreamer1.0, OpenCV 3.4.6, Raspicam AVA, Python 3 (+ virtual environment "cv") for Raspberry pi 1 and Raspberry pi Zero.

"raspbian_stretch_kinetic_ocv348_rpi3b.img" - Image based on Raspbian lite (November, 2019) with ROS Kinetic (ros-comm), gstreamer1.0, OpenCV 3.4.8, Raspicam AVA, Python 3 (+ virtual environment "cv") for Raspberry pi 3.

"image-shrink.sh" Shell script from https://www.raspberrypi.org/forums/viewtopic.php?t=192889 by user RonR. 

Script usage:
"./image-shrink.sh imagefile [Additional MB]

The image file will be shrunk to its absolute minimum size plus an optional number of additional megabytes."
