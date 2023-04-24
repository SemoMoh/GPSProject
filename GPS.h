/*
 *  GPS driver
 */

#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"

uint8_t readGPSChar();
void readGPSString();
double calcDistBetween ( double latComp , double lonComp );
double calcDistToEnd();

#endif /* GPS_H_ */
