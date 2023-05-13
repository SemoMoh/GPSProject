#ifndef LCD_H_
#define LCD_H_



// Include necessary header files
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include <string.h>
#include "GPS.h"

// Global Variables
extern int fix; // Fixation value (defined in another file) 
extern double latEnd; // Target destination latitude value (defined in another file)
extern double lonEnd; // Target destination longitude value (defined in another file)
extern double longitude; // Longitude value (defined in another file)
extern double latitude; // Latitude value (defined in another file)
extern double totalDist; // Total distance travelled (defined in another file)
extern char *direction ; // Direction to target destination string

// Define constants 
#define LCDPORT GPIO_PORTB_BASE // Port used for LCD
#define LCDPORTENABLE SYSCTL_PERIPH_GPIOB // Enable the port used for LCD
#define RS GPIO_PIN_0 // Register select pin
#define E GPIO_PIN_1 // Enable pin
#define D4 GPIO_PIN_4 // Data pin 4
#define D5 GPIO_PIN_5 // Data pin 5
#define D6 GPIO_PIN_6 // Data pin 6
#define D7 GPIO_PIN_7 // Data pin 7

#define ROW1 0x80 // Address of first row
#define ROW2 0xC0 // Address of second row
#define ROW3 0x94 // Address of third row
#define ROW4 0xD4 // Address of fourth row

// Function prototypes
void LCD_init(void); // Initializes the LCD module
void LCD_Command(unsigned char c); // Sends a command to the LCD module
void LCD_Show(unsigned char d); // Shows a character on the LCD module
void LCD_Clear(void); // Clears the screen of the LCD module
void LCD_ClearChar(char row, char col); // Clears a specific character from a specific position on the LCD module 
void LCD_PrintLn(char row, char *s); // Prints a string on a specific row of the LCD module 
void LCD_PrintLnByPos(char row, char col, char *s); //Print specific line from position (row, col) 
void LCD_Cursor(char row, char col); //Set cursor 
void DelaySec(double s); //Delay by (s) seconds / e.g (s=1) -> 1 second
void LCD_DestinationMenu(); //Print gate 2, gate 3 , gate 4 
void LCD_ReadDestination(); //Read switch input and choose specific gate  
void LCD_UpdateDistance(); // Update the dstance on the LCD 
void LCD_setTargetDestination(int x); // Set the target destination
void LCD_ReadDistance(); // Print the distance on the LCD
void LCD_TargetReachedMenu(); // Display a message on the LCD when the target is reached
void startMenu(); // Display the start menu on the LCD
void targetReached(); // Called when the target is reached
void trip(); // Function to be called during a trip
void nearReached(); // Function to be called when near the target destination
void doubleToString(double value); // Convert a double value to a string
#endif /* LCD_H_ */
