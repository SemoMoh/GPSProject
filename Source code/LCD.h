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
// Function prototypes
void LCD_Menu(); //Print gate 2, gate 3 , gate 4
void LCD_ReadDestination(); //Read switch input and choose specific gate 
void LCD_UpdateDistance(); // Update the distance on the LCD ----------> Abdo twin
