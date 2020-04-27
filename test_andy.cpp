#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h> // include GPIO library
#include <signal.h> // needed to clean up CTL C abort
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

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

    //IO test code starts here
    
    uLCD_4DGL uLCD(RST); // serial tx, serial rx, reset pin;

    /*******************************************************
     * Uncomment the sections you want to test
     * ****************************************************/
    

    // // Basic test (WORKS!)
    // uLCD.background_color(GREEN);
    // uLCD.cls();
    // uLCD.filled_circle(60, 60, 20, RED);
    // time_sleep(5.0);
    // uLCD.reset();


    // // Displaying image from uSD test (WORKS!)
    // uLCD.background_color(BLACK);
    // uLCD.cls();
    // uLCD.media_init();
    // uLCD.set_sector_address(0x0020, 0x4000); // You will have to change these values based where RAW data is stored (check .GC file)
    // uLCD.display_image(0,0);
    // time_sleep(5.0);
    // // Test media flush
    // // uLCD.flush_media();
    // // time_sleep(5.0);
    // uLCD.background_color(BLUE);
    // uLCD.cls();
    // time_sleep(5.0);


    // // Test writing and reading from uSD (WORKS!)
    // //.... assumes uLCD already setup as in earlier demo code
    // uLCD.cls();
    // uLCD.media_init(); //init SD card for use
    // char datastring[80]="";
    // uLCD.set_sector_address(0,4096); //go to an unused area on SD card
    // //Write Hello SD World to SD card
    // sprintf(datastring,"%s","Hello there, 4096");
    // printf("\n\nWriting to SD:\n\n");
    // for (int i=0; i<strlen(datastring); i++) {
    //     uLCD.write_byte(datastring[i]); //write a byte to SD card
    //     uLCD.putc(datastring[i]); //also send byte to display
    //     printf("%c", datastring[i]);
    // }
    // printf("\n");
    // uLCD.flush_media(); //flush out (write) entire 512 byte sector with 0xFF fills
    // //Now Read back bytes from SD card
    // time_sleep(5.0);

    // uLCD.set_sector_address(0,4096); //reset to start of sector
    // char readchar =' ';
    // printf("\n\nReading SD: \n\n");
    // while (readchar != 0xFF) { //0xFF is padding character at end of bytes
    //     readchar = uLCD.read_byte();  //read a byte from SD card
    //     uLCD.putc(readchar); //also send byte to display
    //     printf("%X", readchar);
    // }
    // printf("\n");
    // time_sleep(5.0);


    // // Test byte address, word read and write (WORKS!)
    // uLCD.cls();
    // uLCD.media_init();
    // uLCD.set_byte_address(0, 3000);
    // uLCD.write_word(0xBEEF);
    // uLCD.flush_media();
    // printf("Writing to SD\n\n");
    // time_sleep(5.0);
    // uLCD.set_byte_address(0, 3000);
    // printf("Reading from SD:\n");
    // int read = uLCD.read_word();
    // printf("%X\n", read);
    // time_sleep(5.0);


    TODO : // Still need to put video on uSD to be able to test 
    // // Displaying video from uSD test
    // uLCD.media_init();
    // uLCD.set_sector_address(0x0000, 0x0000); // You will have to change these values based where RAW data is stored (check .GC file)
    // uLCD.display_video(0,0);
    // time_sleep(5.0);
    // uLCD.reset();

    TODO: // Test display frame



    // End of program check
    uLCD.background_color(GREEN);
    uLCD.cls();
    // Identify the end of the program is successfully reached the return
    time_sleep(3.0);
    uLCD.reset();

    return 0;
}
