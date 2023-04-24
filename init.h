#ifndef INIT_H_
#define INIT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

void UART0_init(void);           // Function to initialise UART0 and GPIO for PA0 and PA1
void UART5_init(void);           // Function to initialise UART5 and GPIO for PE4 and PE5
void setCLkFreq(uint8_t f);      // Function to set a needed clock frequency


#endif /* INIT_H_ */
