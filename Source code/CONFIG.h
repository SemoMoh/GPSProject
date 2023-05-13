#ifndef CONFIG_H_
#define CONFIG_H_

// Include necessary libraries and header files
#include "inc/tm4c123gh6pm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"

// Include custom header files
#include "GPIO.h"
#include "GPS.h"
#include "LCD.h"
#include "PUTTY.h"

extern bool startMenuFlag;

// Function prototypes
void init();
void run();

#endif /* CONFIG_H_ */
