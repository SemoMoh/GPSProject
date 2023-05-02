#include <stdbool.h>
#include <stdint.h>
#include <lcd.h>

#include "inc/hw_memmap.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

// Global Variables
char globalArray[10];

// Functions
void SW_init(){
    SYSCTL_RCGCGPIO_R |= 0x00000020; // 1) F clock
    while((SYSCTL_PRGPIO_R & 0x20) == 0); // delay
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock PortF PF0
    GPIO_PORTF_CR_R |= 0x11; // allow changes to PF4,PF0
    GPIO_PORTF_AMSEL_R = 0x00; // 3) disable analog function
    GPIO_PORTF_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
    GPIO_PORTF_DIR_R &= ~0x11; // 5) PF4,PF0 input
    GPIO_PORTF_AFSEL_R = 0x00; // 6) no alternate function
    GPIO_PORTF_PUR_R |= 0x11; // enable pullup resistors on PF4,PF0
    GPIO_PORTF_DEN_R |= 0x11; // 7) enable digital pins PF4-PF0
    GPIO_PORTF_DATA_R &= ~0x11;
}

bool sw1_input(void){
  switch(GPIO_PORTF_DATA_R & 0x10){
    case 0x10:
      return 1;                       // 1 for not pushed
    default:
      return 0;                       // 0 for pushed
  }
}

bool sw2_input(void){
    switch(GPIO_PORTF_DATA_R & 0x01){
    case 0x01:
      return 1;                       // 1 for not pushed
    default:
      return 0;                       // 0 for pushed
  }
}

void LCD_init() {

        SysCtlPeripheralEnable(LCDPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, RS,  0x00);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);


        LCD_Command(0x0F); //Turn on Lcd
        LCD_Clear(); //Clear screen

}

void LCD_Command(unsigned char c) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);

        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

}

void LCD_Show(unsigned char d) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) ); // upper nibble
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 ); // lower nibble
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);

        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);
        SysCtlDelay(50000);

}

void LCD_Cursor(char row, char col){

    switch(row){
     case 0:
         LCD_Command(ROW1 + (col % 16));
         break;
     case 1:
         LCD_Command(ROW2 + (col % 16));
         break;
     case 2:
         LCD_Command(ROW3 + (col % 16));
         break;
     case 3:
         LCD_Command(ROW4 + (col % 16));
         break;
     default:
         LCD_Command(ROW4 + (col % 16));
     }

}

void LCD_Clear(void){

        LCD_Command(0x01);
        SysCtlDelay(10);

}

void LCD_PrintLn(char row, char *s) {
    LCD_Cursor(row, 0);
    int i;
    for (i=0; i<strlen(s); i++) {
            if(s[i] == '\0') {
                break;
            }
            LCD_Show(s[i]);
        }
}

void LCD_PrintByPos(char row, char col, char *s) {
    LCD_Cursor(row, col);
    int i;
    for (i=0; i<strlen(s); i++) {
        if(s[i] == '\0') {
            break;
        }
        LCD_Show(s[i]);
    }
}

void LCD_ClearChar(char row, char col){
     LCD_Cursor(row, col);
     LCD_Show(' ');
     LCD_Cursor(row, col);
}
void DelaySec(double s){
    SysCtlDelay(s* (16000000/3));
}

void LCD_Menu(){
    LCD_Clear();
    LCD_PrintByPos(0,0,"Choose Destination:");
    DelaySec(1.5);

    LCD_PrintByPos(1,0," Gate 2");
    DelaySec(0.75);

    LCD_PrintByPos(2,0," Gate 3");
    DelaySec(0.75);

    LCD_PrintByPos(3,0," Gate 6");
}

void LCD_setTargetDestination(int x)
{
    if (x==1)
    {   /*Gate 2 */
        latEnd=30.0646014;
        lonEnd=31.2773738;
        LCD_PrintByPos(1,0,"lat: 30.0646014"); // print latitude
        LCD_PrintByPos(2,0,"long: 31.2773738"); // print longitude
        LCD_PrintByPos(3,0,"Status: Starting..."); // print status
        while(fix == 0) // flag = fix;
        {
           readGPSString();
           NMEA_Type();
           doubleToString(fix);
           printString(globalArray);
        }
        LCD_PrintByPos(3,0,"Status: Connected.");
        DelaySec(2);
    }
    else if (x==2)
    {   /*Gate 3*/
        latEnd=30.063907;
        lonEnd=31.2776239;
        LCD_PrintByPos(1,0,"lat: 30.063907"); // print latitude
        LCD_PrintByPos(2,0,"long: 31.2776239"); // print longitude
        LCD_PrintByPos(3,0,"Status: Starting..."); // print status
        while(fix == 0) // flag = fix;
        {
            readGPSString();
            NMEA_Type();
            doubleToString(fix);
            printString(globalArray);
        }
        LCD_PrintByPos(3,0,"Status: Connected.");
        DelaySec(2);
    }
    else
    {   /*Gate 6*/
        latEnd=30.0648797;
        lonEnd=31.2805086;
        LCD_PrintByPos(1,0,"lat: 30.0648797"); // print latitude
        LCD_PrintByPos(2,0,"long: 31.2805086"); // print longitude
        LCD_PrintByPos(3,0,"Status: Starting..."); // print status
        while(fix == 0) // flag for succesful gps connection
        {
            readGPSString();
            NMEA_Type();
            doubleToString(fix);
            printString(globalArray);
        }
        LCD_ClearChar(3,18);
        LCD_PrintByPos(3,0,"Status: Connected.");
        DelaySec(2);
    }
}

void LCD_ReadDestination(){
    bool flag = true;
    uint8_t i = 1;
    uint8_t p = 1;
    while(flag){
        // read switch input
        if(!sw1_input() && sw2_input()){
            LCD_ClearChar(p,0);
            LCD_Cursor(i, 0); // move 1 row
            LCD_Show('>');
            p = i;
            i++;
            SysCtlDelay((1200000/3));
            if(i > 3) { i = 1; }
        }
        else if (sw1_input() && !sw2_input()){
            switch(p){
            case 1:
                LCD_Clear();
                LCD_PrintLn(0, "Gate 2:");
                flag = false;
                LCD_setTargetDestination(p);
                break;
            case 2:
                LCD_Clear();
                LCD_PrintLn(0, "Gate 3:");
                flag = false;
                LCD_setTargetDestination(p);
                break;
            case 3:
                LCD_Clear();
                LCD_PrintLn(0, "Gate 6:");
                flag = false;
                LCD_setTargetDestination(p);
                break;
            }
        }
        else{
            continue;
        }
    }

    DelaySec(2);
}

void LCD_ReadDistance(){
    LCD_Clear();

    LCD_PrintLn(0,"DistToEnd:");   // start from 15
    doubleToString(calcDistToEnd());
    LCD_PrintByPos(0,10, globalArray);

    LCD_PrintLn(1,"DistMoved:");   // start from 15
    calcDistAcc();
    doubleToString(totalDist);
    LCD_PrintByPos(1,10,globalArray );

    //LCD_PrintLn(2,direction);
}

void LCD_UpdateDistance(){

    // update Remaining Distance
    doubleToString(calcDistToEnd());
    LCD_PrintByPos(0,10, globalArray);

    // update Distance Moved'
    calcDistAcc();
    doubleToString(totalDist);
    LCD_PrintByPos(1,10,globalArray );

    // update Direction
    // showDirct();
    // LCD_PrintLn(3,direction);

}

void LCD_TargetReached(){
    LCD_Clear();
    LCD_PrintLn(0, "Target Reached ;)");
    LCD_PrintLn(2,"DistanceMoved: ");   // start from 15
    calcDistAcc();
    doubleToString(totalDist);
    LCD_PrintByPos(2,15,globalArray );
}
