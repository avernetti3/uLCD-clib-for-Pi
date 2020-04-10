#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <pigpio.h> // include GPIO library
#include <signal.h> // needed to clean up CTL C abort
#include <sys/types.h>
#include <unistd.h>

#define TXD 14 // TXD pin is GPIO_14
#define RXD 15 // RXD pin is GPIO_15

// Called when CTL C or STOP button hit
static void err_handler (int sig){
	gpioTerminate(); //release GPIO locks & resources
	signal(SIGINT, SIG_DFL); //exit program
	kill(getppid(), SIGINT); //kill it off
	kill(getpid(), SIGINT);
	exit(0);
}
static void exit_handler(void) {
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
   char *devtty = (char *)"/dev/ttyS0";
   gpioSetMode(TXD, PI_ALT0); // set TXD pin to alternative mode 0 (TXD0)
   gpioSetMode(RXD, PI_ALT0); // set LED pin to alternative mode 0 (RXD0)
   
   int uLCDhandle = serOpen(devtty, 9600, 0); // open a serial device at a specified baud rate
   std::cout<<"serialHandle: "<< uLCDhandle << "\n\r";
   if((uLCDhandle == PI_NO_HANDLE)||(uLCDhandle == PI_SER_OPEN_FAILED)){
       std::cout <<"ERROR: PI_NO_HANDLE or PI_SER_OPEN_FAILED.\n\r";
       return -1;
   }
   time_sleep(5.0);   
   if( serClose(uLCDhandle)!= 0 ) {
       std::cout <<"ERROR: PI_BAD_HANDLE.\n\r";
       return -1;
   }

    while(1){
	time_sleep(5.0);         
   }

   gpioTerminate();
   return 0;
}
