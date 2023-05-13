// This header file defines functions for initializing and using the GPS module to calculate distance and direction.

#ifndef GPS_H_
#define GPS_H_

// Include necessary header files 
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GPIO.h"

// Define constants
#define RADIUS_OF_EARTH 6371000 // Radius of the Earth in meters 

// Function prototypes
void GPS_init(void); // Initializes the GPS module 
uint8_t readGPSChar(); // Reads a single character from the GPS module 
void readGPSString(); // Reads a string of characters from the GPS module 

double calcDistBetween ( double latComp , double lonComp ); // Calculates the distance between two coordinates in meters 
double calcDistBetweenPoints( double latComp1 , double lonComp1,double latComp , double lonComp); 
double calcDistToEnd(); // Calculates the distance to the end point in meters 
void calcDistAcc(); // Calculates the distance moved in meters 
void decisionLED(); // Determines which LED to light up based on the distance to end 
void showDirct(); // Displays the direction of travel on the LCD 
double absolute(double lat, double lg); //calculate the absolute of a vector 


#endif /* GPS_H_ */
