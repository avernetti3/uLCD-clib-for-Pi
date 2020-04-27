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
`printf()`: this uses `getc()`. `getc()` works it is hard to make `printf()` work, since Class `uLCD_4DGL` inherits from `public Stream` class, which is a mbed os class. I commented it out because `Stream` class does not exist in Pi.

`set_font()`, `set_font_size()` and `text_string()`: FONT_7X8 is the only built-in font. Hence the first two do not work with other font size. Use `text_width()` and `text_height()` instead. `text_string()` works if the `font` argument is FONT_7X8, since it calls `set_font()` within.

`read_pixel()`: does not return the right value. always respond with `0xa9a9`.

`pen_size()`: this function seems to hang the program entirely.

## Working Functions
```c++
class uLCD_4DGL // TODO: public Stream
{
public :
    uLCD_4DGL(unsigned rst);
    ~uLCD_4DGL();
    void cls();
    void reset();
    void baudrate(int speed); // Only support a handful of speed options
    void background_color(int color); // need to cls() to take effect
    void textbackground_color(int color);
    void display_control(char mode); // change display orientation
    void display_power(char mode); //uLCD-144-G2 does not support Contrast ‘levels’, values from 1-15 turn the display ‘On’, 0 turn the Display ‘Off’
    void set_volume(char value); // not supported. no internal speaker for testing.
    // Graphics Commands
    void circle(int x , int y , int radius, int color);
    void filled_circle(int x , int y , int radius, int color);
    void triangle(int, int, int, int, int, int, int);
    void line(int, int, int, int, int);
    void rectangle(int, int, int, int, int);
    void filled_rectangle(int, int, int, int, int);
    void pixel(int, int, int);
    TODO : int  read_pixel(int, int);
    TODO : void pen_size(char);
    void BLIT(int x, int y, int w, int h, int *colors);
    // Text Commands
    TODO : void set_font(char);
    TODO : void set_font_size(char width, char height);  
    void text_mode(char);
    void text_bold(char);
    void text_italic(char);
    void text_inverse(char);
    void text_underline(char);
    void text_width(char);
    void text_height(char);
    void text_char(char, char, char, int);
    TODO : void text_string(char *, char, char, char, int);
    void locate(char, char);
    void color(int);
    void putc(char);
    void puts(char *);
    //Media Commands
    int media_init();
    void set_byte_address(int, int); // Offset number of bytes from beginning
    void set_sector_address(int, int); // Offset number of sectors (512 bytes) from beginning 
    char read_byte();
    int  read_word();
    void write_byte(int);
    void write_word(int);
    void flush_media(); // Needed after a write to SD card, pads the rest of the sector with 0xFF
    void display_image(int, int);
    TODO : void display_video(int, int);
    TODO : void display_frame(int, int, int);
protected :
    //used by printf
    virtual int _putc(int c);
    void freeBUFFER  (void);
    void writeBYTE   (char);
    void writeBYTEfast   (char);
    int  writeCOMMAND(char *, int);
    int  writeCOMMANDnull(char *, int);
    TODO : int  readVERSION (char *, int);
    TODO : int  getSTATUS   (char *, int);
    TODO : int  version     (void);
};
```