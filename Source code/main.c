
#include "CONFIG.h"


// Main function
int main(){
    init();
    while(1){
        run();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * This function initializes the necessary components for the program to run.
 * It sets the clocking to run directly from the internal oscillator at 16 MHz,
 * initializes UART0 and UART5 for Putty and GPS respectively,
 * initializes the switch and LEDs, and initializes the LCD.
 */
void init(){
    // Set the clocking to run directly from the internal oscillator at 16 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_INT | SYSCTL_MAIN_OSC_DIS);

    Putty_init(); // Initialize UART0
    GPS_init(); // Initialize UART5
    GPIO_PF_init(); // Initialize switch and LEDs
    LCD_init(); // Initialize LCD
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * This function runs the main logic of the program.
 * If the start menu flag is false, it prints the start menu on the LCD.
 * If the distance to the end is greater than or equal to 11, it means that we are on a trip to the destination.
 * If the distance to the end is less than 11 but greater than or equal to 6, it means that we are near the destination.
 * Otherwise, it means that we have arrived out destination
 */
void run(){
    if(startMenuFlag == false){
        startMenu();
    }
    if(calcDistToEnd() >= 11){
        trip();
    }
    else if(calcDistToEnd()<11 && calcDistToEnd()>=6 ){
        nearReached();
    }
    else{
        targetReached();
    }
}
