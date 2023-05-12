// This header file defines functions for initializing and using the UART interface to communicate with Putty.

#ifndef PUTTY_H_
#define PUTTY_H_

// Include necessary header files
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>

// Function prototypes
void Putty_init(void); // Initializes the UART interface for communication with Putty
void printChar(uint8_t c); // Sends a single character to UART0
void printString(char * str); // Sends a string of characters to UART0

#endif /* PUTTY_H_ */
