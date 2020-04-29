#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h> // include GPIO library
#include <signal.h> // needed to clean up CTL C abort
#include <sys/types.h>
#include <unistd.h>

#include "uLCD_4DGL.h"

#define RST 18 // RST pin is GPIO_18

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

    //code starts here
    
    int img[1000]= {
16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16055032, 16119797, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 15988468, 14139067, 15592940, 16185847, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16054004, 16054004, 16053747, 16119540, 15792374, 14321024, 14525601, 15989754, 16119283, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16054004, 16054004, 16053747, 16119797, 15660274, 14587280, 14044484, 14534341, 16186875, 15987954, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16054004, 16054004, 16053747, 16119797, 15659760, 14387845, 14642278, 14446698, 15131360, 16251897, 15987954, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16054004, 16119540, 15987697, 16119540, 15593710, 14386304, 14972270, 14970471, 14193551, 15791603, 16119796, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16053747, 15791346, 16055289, 16317947, 15461353, 14449011, 14577770, 14711412, 14311512, 14930382, 16055032, 15856368, 15922418, 15922418, 15922418, 15922418, 15922418, 15988211, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 15987954, 16120568, 14139838, 14398641, 15394790, 15528946, 14981525, 14181469, 13988720, 14968156, 14530485, 16515071, 16448505, 16449019, 16449019, 16449018, 16514298, 16448762, 16317433, 16185590, 16054003, 15922418, 15922418, 15988467, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16449533, 15656419, 14770264, 14707813, 14000285, 13018788, 13132638, 10181724, 12146513, 13932436, 13883350, 13093063, 12566976, 12435133, 12501183, 12961477, 13685456, 14475229, 15396074, 16119797, 16449018, 16382969, 16054004, 15922418, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 15791089, 14935267, 12962248, 9795702, 8871775, 7426641, 5920600, 6055013, 5661283, 5857121, 13263452, 9260363, 2967627, 4999242, 4606026, 4671562, 4737099, 4934734, 5658456, 7105902, 9277326, 11908789, 14343386, 16054004, 16514555, 16119797, 15922418, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16317176, 12961734, 4672074, 2170148, 5332576, 5727848, 6187113, 6645351, 6447458, 6972773, 5071716, 11102309, 12347492, 5400168, 7170667, 6842730, 6908523, 6908523, 6842730, 6711144, 6316386, 5526871, 4737355, 5461334, 8816519, 12895941, 15790832, 16448762, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
15988467, 16054004, 14540765, 11053481, 7039594, 6644580, 6644838, 6513509, 5724249, 6513508, 6120549, 7627363, 13396580, 6774367, 6251365, 6579045, 6513765, 6447972, 6447972, 6513765, 6579558, 6776937, 6908523, 6710887, 5790042, 4605769, 8026747, 13553614, 16317176, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16317176, 16580092, 9869463, 5263699, 6842730, 6382179, 5724249, 6513765, 6775909, 4939874, 13331817, 10577508, 4349022, 6841702, 6447972, 6447972, 6513765, 6513765, 6513765, 6513765, 6513765, 6513765, 6711144, 6908523, 6119007, 3815997, 12830147, 16448762, 15922418, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 15790832, 15988211, 9342863, 5526870, 6776937, 6316386, 5855835, 6579558, 6841445, 4546915, 12282983, 13201002, 3692634, 6644066, 6447972, 6250593, 6579558, 6513765, 6513765, 6513765, 6579301, 6382179, 6316386, 6513765, 6842730, 6382179, 6184800, 15198695, 16251383, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16119797, 16514555, 16251384, 8421761, 5855835, 6711144, 6513765, 6513765, 6513765, 6775909, 5005923, 10839137, 15037807, 6709087, 5593435, 6579301, 6185057, 6513765, 6513765, 6513765, 6513765, 6513765, 6513765, 5921628, 6513765, 6513765, 6513765, 5000527, 10527393, 16448762, 15922418, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 15725039, 13882835, 10987944, 6842986, 6645351, 6579558, 6316386, 6316386, 6579558, 6710373, 5989477, 9392723, 15365743, 10381157, 4742751, 6446687, 6382179, 6316386, 6513765, 6513765, 6513765, 6513765, 6579558, 6053214, 5790041, 6645351, 6184800, 6316129, 5197906, 12961477, 16646141, 15922418, 15922418, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16317176, 12764355, 5395543, 3289911, 5131856, 6052958, 6711144, 6316129, 6119264, 6579301, 6710887, 5857891, 9783884, 14380906, 13201258, 4873311, 6184028, 6250593, 6579558, 6776937, 6645351, 6579558, 6513765, 6513765, 6645351, 5790042, 6053214, 6842730, 7040109, 5987164, 6053214, 13422285, 16514555, 16317176, 16185590, 16054004, 16054004, 16054004, 16054004, 15988211, 
16054004, 16054004, 15330539, 13554128, 10922153, 7961726, 6119008, 5131599, 6316386, 7105131, 5398882, 10113358, 15036263, 14578798, 13921125, 7958383, 7107187, 6052700, 5526870, 5658199, 6052957, 6513765, 6776937, 6579558, 6513765, 6447972, 5658456, 7171952, 12501699, 8619398, 5263184, 5263442, 11053480, 14606815, 15725039, 16054004, 16185590, 16054004, 16185590, 16185590, 
16054004, 16054004, 16251382, 16383225, 16317176, 15330539, 13422544, 10133151, 6053215, 5262928, 6778222, 12889260, 12617349, 12411486, 14182239, 11508378, 13226707, 12830406, 11646134, 9935515, 8093311, 6316387, 5526614, 6447972, 6579558, 6579558, 6053214, 6842986, 13159629, 13752022, 10593445, 6974573, 2631982, 3684667, 6447715, 7698038, 8356224, 7237488, 8948104, 15659246, 
16054004, 16054004, 15988211, 15987954, 15988211, 16185589, 16251383, 15659504, 12238269, 8422276, 13356750, 15660532, 13687514, 6845814, 6901069, 8221299, 14278109, 16251383, 15922418, 15462125, 14804195, 13356751, 10461859, 6448229, 6316129, 6908523, 5658198, 10527653, 14738403, 15988211, 15462125, 14212059, 12566977, 11251117, 10330015, 10066586, 10000793, 10395551, 12303803, 15725039, 
16054004, 16054004, 16054004, 16054004, 16054004, 15988211, 15988211, 16119797, 16119797, 15856625, 16185846, 16119540, 16382712, 15264231, 7962495, 1056807, 11777462, 16382969, 15988211, 16119797, 16185590, 16185590, 15659247, 13159628, 6711401, 6382179, 5790042, 10593445, 16119798, 16054004, 16119797, 16251383, 16382969, 16382969, 16382969, 16448506, 16448762, 16514298, 16514555, 16119797, 
16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 15988211, 16054004, 16119540, 15988211, 16053747, 15922418, 16317176, 15658989, 10526880, 5066577, 14935780, 16317176, 15922418, 15988211, 15988211, 16054004, 16317176, 13817044, 6514023, 5000526, 8093053, 15659246, 16251383, 15922418, 15988211, 15988211, 15988211, 15988211, 15988211, 15988211, 15922418, 15922418, 16054004, 
16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 15988468, 16054004, 16054004, 16054004, 15922419, 16185590, 16382969, 13751250, 15264488, 16251383, 15988211, 16054004, 16054004, 16054004, 15988211, 16448762, 14672352, 8948362, 2302760, 9935256, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 15988211, 15988211, 16448762, 16185590, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 15922418, 16317176, 16119797, 12106425, 6448228, 15132902, 16251383, 15988211, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 
16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 15922418, 15988467, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 15988211, 16119797, 16382969, 15593453, 15988467, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004, 16054004
};

    uLCD_4DGL uLCD(RST); // serial tx, serial rx, reset pin;
    uLCD.baudrate(115200); //jack up baud rate to max for fast display
    
    uLCD.background_color(BLACK);
    uLCD.cls();

    uLCD.filled_circle(60, 50, 30, 0xFF00FF);
    uLCD.triangle(120, 100, 40, 40, 10, 100, 0x0000FF);
    uLCD.line(0, 0, 80, 60, 0xFF0000);
    uLCD.filled_rectangle(50, 50, 100, 90, 0x00FF00);
    uLCD.pixel(60, 60, RED);

    uLCD.BLIT(80, 100, 40, 25, img);

    time_sleep(5.0);

    return 0;
}