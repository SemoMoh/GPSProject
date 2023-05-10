#include "CONFIG.h"
extern bool startMenuFlag;


int main(){
    init();
    while(1){
        run();

    }
}

void init(){
    // Set the clocking to run directly from the internal oscillator at 16 MHz
       SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_INT | SYSCTL_MAIN_OSC_DIS);

       Putty_init(); // Initialize UART0
       GPS_init(); // Initialize UART5
       GPIO_PF_init(); //Initiallize switch and LEDs
       LCD_init();

}
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
