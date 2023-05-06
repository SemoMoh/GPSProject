#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

bool sw1_input(void);                  //This function reads the input from switch 1 (PF4) and returns 1 if the switch is not pushed and 0 if it is pushed.
bool sw2_input(void);                 //This function reads the input from switch 2 (PF0) and returns 1 if the switch is not pushed and 0 if it is pushed.
void RGB_output(unsigned char data); //This function outputs the given data to the RGB LEDs. It resets the RGB LEDs and then turns on the needed LEDs based on the given data.



#endif /* GPIO_H_ */
