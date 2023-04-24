#include "GPS.h"
#include <stdio.h>
#include <string.h>
 
/* 
 * Global variables used
 */
extern char receivedChar;
extern uint32_t strGPS_counter;
extern char strGPS[];

//end points
extern double latEnd;
extern double lonEnd;

//global variables used for the next functions
extern double longitude;
extern double latitude;
extern char latSTR[10];
extern char lonSTR[10];
extern double altitude;
extern char time[10];
extern double speed;
extern int fix;
extern char*token;
extern int fieldCount;

extern int i = 0; // counter to keep track of the current token position
extern double latPre; //previous latitude
extern double lonPre; //previous longitude
extern double totalDist;
extern bool reached; 
/**
 * Function declration
 */


////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Converts a DDMM.MMMM format value to a decimal degree value.
 *
 * This function converts a DDMM.MMMM format value to a decimal degree value. It calculates the degrees and minutes separately and then combines them to get the final result.
 *
 * @param dd6m The DDMM.MMMM format value to be converted.
 * @return double The decimal degree value.
 */

double dd6m_TO_degree(double dd6m){
    int dd= dd6m / 100 ;
    double _6m = (dd6m - dd * 100) / 60;
    return dd+_6m;
}

/**
 * @brief Checks if a string is a substring of another string.
 *
 * This function checks if the string `check` is a substring of the string `string`. It does this by checking each position in `string` for `check`.
 *
 * @param check The string to check if it is a substring.
 * @param string The string to check for the substring in.
 * @return bool Returns true if `check` is a substring of `string`, false otherwise.
 */
int i;
bool is_substring(char *check, char *string)
{
  // get the length of both strings
  int slen = strlen(string);
  int clen = strlen(check);

  // we can stop checking for check in string at the position it will no longer
  // possibly fit into the string
  int end = slen - clen + 1;

  // check each position in string for check
  int i = 0;
  for (i = 0; i < end; i++)
  {
    // assume the check string is found at this position
    bool check_found = true;

    // check each index of the check string to see if it matches with the
    // corresponding character in string at index i onwards
    int j = 0;
    for ( j = 0; j < clen; j++)
    {
      // if we find a non-matching character, we know that check is not
      // found here and we can stop checking now
      if (check[j] != string[i + j])
      {
        check_found = false;
        break;
      }
    }

    // if we found no non-matching characters, we found that check IS a
    // substring of string (at position i) and we can stop checking
    if (check_found) return true;
  }

  // if at no position in string did we find check it is NOT a substring
  return false;
}

/**
 * @brief Reads and parses GGA data from a GPS device.
 *
 * This function reads and parses GGA data from a GPS device. It tokenizes the `strGPS` string using the `strtok` function and then processes each field based on its position. 
 * It extracts the time, latitude, longitude, fixation, and altitude from the GGA data and stores them in the corresponding variables.
 *
 * @param void
 * @return void
 */
void readGGA(){
    fieldCount = 0;
    token = strtok(strGPS, ",");
        while (token != NULL) {
            switch (fieldCount) {
                case 1://time
                   // time = strcpy (token);
                    break;

                case 2: // latitude
                    latitude = dd6m_TO_degree( atof( token ) );
                    ////////////////////////////////////////temp
                    i=0;
                    while(*token != '\0'){
                        latSTR[i++]= *token;
                        token++;
                    }
                    latSTR[i]='\0';
                    ////////////////////////////////////////end temp
                    break;

                case 3: // north/south
                    if (*token == 'S') {
                       latitude = -1*latitude;
                    }
                    break;

                case 4: // longitude
                    longitude = dd6m_TO_degree( atof( token ) );

                    ////////////////////////////////////////temp
                    i=0;
                    while(*token != '\0'){
                        lonSTR[i++]= *token;
                        token++;
                    }
                    lonSTR[i]='\0';
                    ////////////////////////////////////////end temp

                    break;

                case 5: // east/west
                    if (*token == 'W') {
                        longitude = -1*longitude;
                    }
                    break;

                case 6: // fixation
                    fix=atoi(token);
                    break;

                case 9: // altitude
                    altitude = atof(token);
                    break;

            }
            fieldCount++;
            token = strtok(NULL, ",");
        }
}

/**
 * @brief Reads and parses RMC data from a GPS device.
 *
 * This function reads and parses RMC data from a GPS device. It tokenizes the `strGPS` string using the `strtok` function and then processes each field based on its position. 
 * It extracts the time, latitude, longitude and altitude from the RMC data and stores them in the corresponding variables.
 *
 * @param void
 * @return void
 */
void readRMC(){
    fieldCount = 0;
    token = strtok(strGPS, ",");
        while (token != NULL) {
            switch (fieldCount) {
                case 1://time
                   // time = token;
                    break;

                case 3: // latitude
                    latitude = dd6m_TO_degree( atof( token ) );
                    ////////////////////////////////////////temp
                    i=0;
                    while(*token != '\0'){
                        latSTR[i++]= *token;
                        token++;
                    }
                    latSTR[i]='\0';
                    ////////////////////////////////////////end temp
                    break;

                case 4: // north/south
                    if (*token == 'S') {
                       latitude = -1*latitude;
                    }
                    break;

                case 5: // longitude
                    longitude = dd6m_TO_degree( atof( token ) );
                    ////////////////////////////////////////temp
                    i=0;
                    while(*token != '\0'){
                        lonSTR[i++]= *token;
                        token++;
                    }
                    lonSTR[i]='\0';
                    ////////////////////////////////////////end temp
                    break;


                case 6: // east/west
                    if (*token == 'W') {
                        longitude = -1*longitude;
                    }
                    break;

                case 2: // fixation
                    k=atoi(token);
                    switch (k){
                        case 'A':
                              fix = 1 ;
                              break;
                        case 'V':
                              fix = 0 ;
                              break;
                    }
                    break;

                case 9: // altitude
                    altitude = atof(token);
                    break;

            }
            fieldCount++;
            token = strtok(NULL, ",");
        }
}

extern int k; // variable used in readGLL and readRMC functions, it used in the fixation part
/**
 * @brief Reads and parses GLL data from a GPS device.
 *
 * This function reads and parses GLL data from a GPS device. It tokenizes the `strGPS` string using the `strtok` function and then processes each field based on its position. 
 * It extracts the time, latitude, and longitude from the GLL data and stores them in the corresponding variables.
 *
 * @param void
 * @return void
 */
void readGLL(){
    fieldCount = 0;
    token = strtok(strGPS, ",");
        while (token != NULL) {
            switch (fieldCount) {
                case 5://time
                //    time = token;
                    break;

                case 1: // latitude
                    latitude = dd6m_TO_degree( atof( token ) );
                    ////////////////////////////////////////temp
                    i=0;
                    while(*token != '\0'){
                        latSTR[i++]= *token;
                        token++;
                    }
                    latSTR[i]='\0';
                    ////////////////////////////////////////end temp

                    break;

                case 2: // north/south
                    if (*token == 'S') {
                       latitude = -1*latitude;
                    }
                    break;

                case 3: // longitude
                    longitude = dd6m_TO_degree( atof( token ) );
                    ////////////////////////////////////////temp
                    i=0;
                    while(*token != '\0'){
                        lonSTR[i++]= *token;
                        token++;
                    }
                    lonSTR[i]='\0';
                    ////////////////////////////////////////end temp

                    break;

                case 4: // east/west
                    if (*token == 'W') {
                        longitude = -1*longitude;
                    }
                    break;

                case 6: // fixation
                    k= atoi(token);
                    switch (k){
                    case 'A':
                        fix = 1 ;
                        break;
                    case 'V':
                        fix = 0 ;
                        break;
                    }
                    break;


            }
            fieldCount++;
            token = strtok(NULL, ",");
        }
}

char c1[] = "$GPGLL"; // define character array for NMEA sentence type GPGLL
char c2[] = "$GPRMC"; // define character array for NMEA sentence type GPRMC
char c3[] = "$GPGGA"; // define character array for NMEA sentence type GPGGA

/**
 * @brief Checks if certain NMEA sentence types (GPGLL, GPRMC, GPGGA) are substrings of strGPS
 * and calls the appropriate function (readGLL, readRMC, readGGA) to read the data.
 * 
 * @param void
 * @return void
 */
void NMEA_Type(){
        // check if c1 is a substring of s1, report the results
        if (is_substring(c1,strGPS)) // check if GPGLL is a substring of strGPS
         {
           readGLL(); // call function to read GPGLL data
         }
        else if (is_substring(c2,strGPS)) // check if GPRMC is a substring of strGPS
         {
           readRMC(); // call function to read GPRMC data
         }
        else if(is_substring(c3,strGPS)) // check if GPGGA is a substring of strGPS
        {
           readGGA(); // call function to read GPGGA data
        }
}

/**
 * @brief Receives a single character using UART5.
 *
 * This function receives a single character using the UART5 peripheral on a
 * TM4C123GH6PM microcontroller. The function waits until the UART5 receive
 * FIFO is not empty before reading the character from the UART5 data register.
 * If there are any errors or if the received value is a garbage value, the function
 * returns a null character.
 *
 * @param None
 * @return The received character or a null character if there are any errors.
 */
uint8_t readGPSChar(){
    while (UART5_FR_R & (1<<4)){}; // Wait until the UART5 receive FIFO is not empty
    if((UART5_DR_R & 0xFFFFFF00) != 0){
        // Check if there are any errors or if it's a garbage value
        return '\0';
    }
    return (char)(UART5_DR_R & 0xFF); // Read the received character from the UART5 data register
}


/**
 * @brief Receives a string using UART5.
 *
 * This function receive a NMEA string from the GPS,
 * it uses the global var str_GPS to store that string.
 * it calls the function readGPSChar() to get the string elemnts.
 *
 * @param None
 * @return None
 */
void readGPSString(){
    strGPS_counter = 0; // Initialize the GPS string counter to 0
    receivedChar = readGPSChar(); // Read the first character from the GPS
    while(receivedChar != '$'){ // Keep reading until a '$' character is found
        receivedChar = readGPSChar();
    }
    strGPS[strGPS_counter++] = receivedChar; // Store the '$' character in the GPS string
    receivedChar = readGPSChar(); // Read the next character from the GPS
    while(receivedChar != '$'){ // Keep reading and storing characters until another '$' character is found
        strGPS[strGPS_counter++] = receivedChar;
        receivedChar = readGPSChar();
    }
    strGPS[--strGPS_counter] = '\0'; // Replace the last '$' character with a null terminator to end the GPS string
}


/**
 * @brief Calculates the distance between two points on Earth.
 *
 * This function calculates the distance between two points on Earth given their latitudes and longitudes using the Haversine formula.
 *
 * @param latComp The latitude of the first point in degrees.
 * @param lonComp The longitude of the first point in degrees.
 * @return double The distance between the two points in meters.
 */
double calcDistBetween ( double latComp , double lonComp ){
   // Convert latitudes and longitudes from degrees to radians
   double latComp_rad = latComp * 3.14159265359 / 180.0;
   double lonComp_rad = lonComp * 3.14159265359 / 180.0;
   double latitude_rad = latitude * 3.14159265359 / 180.0;
   double longitude_rad = longitude * 3.14159265359 / 180.0;

   // Calculate differences in latitudes and longitudes
   double d_lat = latitude_rad - latComp_rad;
   double d_lon = longitude_rad - lonComp_rad;

   // Calculate the distance using the Haversine formula
   double a = sin(d_lat/2) * sin(d_lat/2) + cos(latComp_rad) * cos(latitude_rad) * sin(d_lon/2) * sin(d_lon/2);
   return ( RADIUS_OF_EARTH * 2 * atan2( sqrt(a), sqrt(1-a)) );
}

/**
 * @brief Calculates the distance to the end point.
 *
 * This function calculates the distance to the end point using the calcDistBetween function.
 *
 * @param void
 * @return double The distance to the end point in meters.
 */
double calcDistToEnd(){
    return calcDistBetween( latEnd , lonEnd );
}


void calcDistAcc(){
    if( latPre==0 && lonPre==0 ){ //start point
        latPre=latitude;
        lonPre=longitude;
        return ;
    }
    totalDist += calcDistBetween (latPre,lonPre);
    latPre=latitude;
    lonPre=longitude;
}


void decisionLED(){
    if(latitude == 0 && longitude == 0 ){
        RGP_output(0x0E);
        return;
    }
    double d=calcDistToEnd();
    if(d < 2.5){ // green on
        RGP_output(0x08);
        reached = true;
    }
    else if(d < 7.5){ //yellow on
        RGP_output(0x04);
    }
    else{ //red on
        RGP_output(0x02);
    }
}
