# uLCD-clib-for-Pi
This is a project that port the uLCD C++ library from mbed to Raspberry Pi (Raspian).

Created by:
<br>Andrew (Andy) Vernetti
<br>Xingyang (Xandy) Liu

Created for:
Georgia Tech ECE4180-A Embedded Systems Design - Final Project

NOTE FOR RASPBERRY PI 3: The Raspberry pi 3 has changed things around a bit: ttyAMA0 now refers to the serial port that is connected to the bluetooth. The old serial port is now called ttyS0. So if you have an RPI3, everywhere you see "ttyAMA0" below, you should read "ttyS0".


_rst = 1;           ->      gpioWrite(_rst, 1); 
_cmd.putc(c);       ->      serWriteByte(_cmd, (unsigned) c);
_cmd.getc();        ->      int = serReadByte(_cmd);
wait_ms(5);         ->      time_sleep(0.005);
wait(3);            ->      time_sleep(3);
wait_us(500);       ->      time_sleep(0.0005);
_cmd.readable()     ->      serDataAvailable(_cmd) != 0
