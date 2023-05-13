// This header file defines functions for initializing GPIO pins, reading switch inputs, and controlling RGB output.
#ifndef GPIO_H_
#define GPIO_H_
// Include necessary header files
#include "inc/tm4c123gh6pm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"


// Function prototypes
void GPIO_PF_init(void); // Initializes GPIO pins for switch inputs and RGB output
bool sw1_input(void); // Reads the state of switch 1
bool sw2_input(void); // Reads the state of switch 2
void RGB_output(unsigned char data); // Sets the colour of the RGB LED based on the input data






#endif /* GPIO_H_ */

