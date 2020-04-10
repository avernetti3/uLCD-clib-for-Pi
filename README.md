# uLCD-clib-for-Pi
This is a project that port the uLCD C++ library from mbed to Raspberry Pi (Raspian).

Created by:
<br>Andrew (Andy) Vernetti
<br>Xingyang (Xandy) Liu

Created for:
Georgia Tech ECE4180-A Embedded Systems Design - Final Project

NOTE FOR RASPBERRY PI 3: The Raspberry pi 3 has changed things around a bit: ttyAMA0 now refers to the serial port that is connected to the bluetooth. The old serial port is now called ttyS0. So if you have an RPI3, everywhere you see "ttyAMA0" below, you should read "ttyS0".