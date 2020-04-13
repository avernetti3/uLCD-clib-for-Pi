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
    printf("uLCD constructed\n");
    //uLCD.printf("\nHello uLCD World\n");
    time_sleep(5.0);
    uLCD.background_color(GREEN); // TODO: background_color not working !!!
    printf("color backgroud\n");
    time_sleep(5.0);
    uLCD.filled_circle(60, 60, 20, RED);
    time_sleep(5.0);
    uLCD.background_color(GREEN); // TODO: background_color not working !!!
    uLCD.putc('A');
    uLCD.putc('B');
    time_sleep(5.0);

    return 0;
}
