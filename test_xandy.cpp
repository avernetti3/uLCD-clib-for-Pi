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
    
    uLCD_4DGL uLCD(RST); // serial tx, serial rx, reset pin;
    //uLCD.printf("\nHello uLCD World\n");
    uLCD.baudrate(115200); //jack up baud rate to max for fast display
    //if demo hangs here - try lower baud rates
    //
    uLCD.background_color(BLUE);
    uLCD.cls();
    time_sleep(5.0);

    return 0;
}
