#include "tivaConfig.h"

#include <string.h>
#include <math.h>
/**
 * Global Variables
 */
double latEnd;
double lonEnd;
char strGPS[80];
double longitude;
double latitude;
char latSTR[10];
char lonSTR[10];
double altitude;
char time[10];
double speed;
int fix;
char*token;
int fieldCount;
char receivedChar;
int i;
double latPre;
double lonPre;
double totalDist;
bool reached;
uint32_t strGPS_counter;

/**
 * main function
 */

int main(){
    // Set the clocking to run directly from the internal oscillator at 16 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_INT | SYSCTL_MAIN_OSC_DIS);

    Putty_init(); // Initialize UART0
    GPS_init(); // Initialize UART5
    GPIO_PFinit(); //Initiallize switch and LEDs

    while(1){
        if(reached == true){ // when reached

        }
        
        else{
       readGPSString();
       NMEA_Type();
       decisionLED();
       calcDistAcc();
       }
   }
}
