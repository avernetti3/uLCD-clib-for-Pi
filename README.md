# uLCD-clib-for-Pi
This is a project that port the uLCD C++ library from mbed to Raspberry Pi (Raspian).

Created by:
<br>Andrew (Andy) Vernetti
<br>Xingyang (Xandy) Liu

Created for:
Georgia Tech ECE4180-A Embedded Systems Design - Final Project

## The Raspberry Pi UARTs 
(https://www.raspberrypi.org/documentation/configuration/uart.md)

By default, on Raspberry Pis equipped with the wireless/Bluetooth module (Raspberry Pi 3 and Raspberry Pi Zero W), the PL011 UART is connected to the Bluetooth module, while the mini UART is used as the primary UART and will have a Linux console on it. On all other models, the PL011 is used as the primary UART.

In Linux device terms, by default, /dev/ttyS0 refers to the mini UART, and /dev/ttyAMA0 refers to the PL011. The primary UART is the one assigned to the Linux console, which depends on the Raspberry Pi model as described above. There are also symlinks: /dev/serial0, which always refers to the primary UART (if enabled), and /dev/serial1, which similarly always refers to the secondary UART (if enabled).

By default, the UART transmit and receive pins are on GPIO 14 and GPIO 15 respectively, which are pins 8 and 10 on the GPIO header.

## How to use UART output on GPIO
We need to enable Serial Port and disable Serial Console. You can do this via either GUI or command line.

GUI: Go to Preferences > Raspberry Pi Configuration > Interfaces > Enable Serial Port and Disable Serial Console.

Command line: sudo raspi-config > 5 Interfacing Options > P6 Serial > No (login shell) > Yes (serial port hardware)

To test UART working correctly, connect TX (GPIO_14) to RX (GPIO_15). I have written a short c program called UARTtest.cpp for testing. You should see the letters A to Z in the command line.

Compile in command line: `g++ -Wall -pthread -o "UARTtest" "UARTtest.cpp" -lpigpio -lrt`

Run in command line: `sudo ./UARTtest`

Troubleshooting: If you do not see the expected result and either see continuous running program with errors, or see program freezing without finishing, first quit the program by hitting Ctrl + C, then go into UARTtest.cpp and change the following line:

`char *devtty = (char *)"/dev/serial0";`

Change `serial0` to `serial1`, or `ttyS0`, or `ttyAMA0`.

## PIGPIO Serial Interface 
(http://abyz.me.uk/rpi/pigpio/cif.html#serOpen)

mbed uLCD_4DGL library      |      PIGPIO c library
---                         |      ---
_rst = 1;                   |      gpioWrite(_rst, 1); 
_cmd.putc(c);               |      serWriteByte(_cmd, (unsigned) c);
_cmd.getc();                |      int = serReadByte(_cmd);
wait_ms(5);                 |      time_sleep(0.005);
wait(3);                    |      time_sleep(3);
wait_us(500);               |      time_sleep(0.0005);
_cmd.readable()             |      serDataAvailable(_cmd) != 0

## TODO: functions that have not been tested / have issues
`background_color()`: not working. Haven't figured it out yet.

`printf()`: this uses `getc()`, which works. but I don't know how to make `printf()` work.

