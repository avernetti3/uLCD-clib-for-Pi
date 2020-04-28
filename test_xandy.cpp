#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h> // include GPIO library
#include <signal.h> // needed to clean up CTL C abort
#include <sys/types.h>
#include <unistd.h>

#include "uLCD_4DGL.h"

// #define TXD 14 // TXD pin is GPIO_14
// #define RXD 15 // RXD pin is GPIO_15
#define RST 18 // RST pin is GPIO_18

// Called when CTL C or STOP button hit
static void err_handler (int sig){
    //printf("err_handler\n");
	gpioTerminate(); //release GPIO locks & resources
	signal(SIGINT, SIG_DFL); //exit program
	kill(getppid(), SIGINT); //kill it off
	kill(getpid(), SIGINT);
	exit(0);
}
static void exit_handler(void) {
    //printf("exit_handler\n");
	gpioTerminate(); //release GPIO locks & resources on exit
}
int main(int argc, char *argv[])
{
    if (gpioInitialise()<0) return 1; // init I/O library
    signal (SIGQUIT, err_handler);// CTL C and STOP button
    signal (SIGINT, err_handler); // GPIO exit & cleanup
    signal (SIGTERM, err_handler);
    signal (SIGABRT, err_handler);
    atexit(exit_handler);  // exit handler cleanup 

    //IO code starts here
    /*
    int img[330] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3681288, 3681288, 3681288, 0, 0, 0, 0, 3681288, 3681288, 3681288, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 3681288, 3681288, 15244328, 3681288, 3681288, 0, 0, 3681288, 3681288, 15244328, 3681288, 0, 0, 
        3681288, 3681288, 3681288, 0, 0, 0, 0, 0, 0, 3681288, 15244328, 15261912, 15244328, 3681288, 3681288, 3681288, 3681288, 15244328, 15261912, 3681288, 0, 0, 
        3681288, 15261912, 3681288, 0, 0, 0, 0, 0, 0, 3681288, 9986072, 15244328, 15244328, 9986072, 15244328, 9986072, 15244328, 9986072, 15244328, 3681288, 3681288, 0, 
        3681288, 15244328, 3681288, 0, 0, 0, 0, 0, 3681288, 3681288, 15244328, 15244328, 15244328, 15244328, 15244328, 9986072, 15244328, 15244328, 15244328, 15244328, 3681288, 3681288, 
        3681288, 9986072, 3681288, 3681288, 0, 0, 0, 0, 3681288, 9986072, 9986072, 15244328, 3681296, 15244328, 15244328, 15244328, 15244328, 3681296, 15244328, 9986072, 3681288, 0, 
        3681288, 3681288, 15244328, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 3681288, 3681288, 
        0, 3681288, 3681288, 9986072, 15244328, 9986072, 15244328, 9986072, 15244328, 9986072, 9986072, 15244328, 15244328, 15261912, 15238344, 15261912, 15244328, 15244328, 15244328, 9986072, 3681288, 0, 
        0, 0, 3681288, 3681288, 3681288, 3681288, 15244328, 9986072, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15261912, 15244328, 15244328, 15244328, 15244328, 15244328, 3681288, 3681288, 
        0, 0, 0, 0, 0, 3681288, 15244328, 15244328, 15244328, 15244328, 9986072, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 3681288, 3681288, 0, 
        0, 0, 0, 0, 0, 3681288, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 3681288, 3681288, 0, 0, 
        0, 0, 0, 0, 0, 3681288, 3681288, 15244328, 15244328, 15244328, 15244328, 15244328, 15244328, 15261912, 15261912, 15244328, 15261912, 15244328, 3681288, 0, 0, 0, 
        0, 0, 0, 0, 0, 3681288, 3681288, 15244328, 15244328, 15261912, 15261912, 15261912, 15244328, 15261912, 15261912, 15244328, 15244328, 15244328, 3681288, 0, 0, 0, 
        0, 0, 0, 0, 0, 3681288, 3681288, 15261912, 15244328, 15244328, 15261912, 15244328, 15261912, 15244328, 15244328, 15261912, 15244328, 3681288, 3681288, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 3681288, 0, 0, 0, 0
    };*/

    uLCD_4DGL uLCD(RST); // serial tx, serial rx, reset pin;
    //uLCD.baudrate(115200); //jack up baud rate to max for fast display
    
    uLCD.background_color(BLACK);
    uLCD.cls();

    uLCD.pen_size(SOLID);
    uLCD.circle(60, 50, 30, 0xFF0000);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(WIREFRAME);
    uLCD.circle(60, 50, 30, 0x00FF00);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(SOLID);
    uLCD.filled_circle(60, 50, 30, 0xFF0000);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(WIREFRAME);
    uLCD.filled_circle(60, 50, 30, 0x00FF00);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(SOLID);
    uLCD.triangle(120, 100, 40, 40, 10, 100, 0xFF0000);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(WIREFRAME);
    uLCD.triangle(120, 100, 40, 40, 10, 100, 0x00FF00);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(SOLID);
    uLCD.filled_rectangle(50, 50, 100, 90, 0xFF0000);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(WIREFRAME);
    uLCD.filled_rectangle(50, 50, 100, 90, 0x00FF00);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(SOLID);
    uLCD.rectangle(50, 50, 100, 90, 0xFF0000);
    time_sleep(3.0);
    uLCD.cls();

    uLCD.pen_size(WIREFRAME);
    uLCD.rectangle(50, 50, 100, 90, 0x00FF00);

    
    //uLCD.filled_rectangle(50, 50, 100, 90, 0x00FF00);
    
    //uLCD.BLIT(10, 10, 22, 15, img);

    time_sleep(5.0);

    return 0;
}
