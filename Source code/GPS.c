#include "GPS.h"

// Global Variables
char receivedChar; // Character received from GPS 
uint32_t strGPS_counter; // Counter for GPS string 
char strGPS[80]; // GPS string 
double longitude; // Longitude value 
double latitude; // Latitude value
double preLatitude; // Previous latitude value  
double preLongitude; // Previous longitude value 
double altitude; // Altitude value 
char time[10]; // Time string 
double speed; // Speed value  
int fix; // Fixation value 
char *token; // Token for parsing GPS string 
int fieldCount; // Field count for parsing GPS string 
int i; // Loop counter variable 
int k; // Loop counter variable 

char c1[] = "$GPGLL"; // GLL NMEA sentence identifier 
char c2[] = "$GPRMC"; // RMC NMEA sentence identifier 
char c3[] = "$GPGGA"; // GGA NMEA sentence identifier 

double latPre; // Previous latitude value for distance calculation 
double lonPre; // Previous longitude value for distance calculation 
double totalDist; // Total distance traveled 

bool reached; // Flag indicating if target destination has been reached 

double tempDist; // Temporary distance variable 

char *direction ; // Direction to target destination string 
double prevLat, prevLong; // Previous latitude and longitude values for direction calculation 
double dotPdt,theta,crossPdt; // Variables for vector calculations 
double vecDirctLat, vecDirctLong, vecLatToEnd, vecLongToEnd; // Vector variables for direction calculation 
bool DirctFlag = false; // Flag indicating if it is the first reading or not 

// End points
double latEnd; // Target destination latitude value 
double lonEnd; // Target destination longitude value 


//////////////////////////////////////////////////////////////////////////////////////////
//Functions
/**
 * @brief Initializes the UART5 peripheral for communication.
 *
 * This function configures the UART5 peripheral
 * for communication using a baud rate of 9600 and 8 data bits, 1 stop bit, and no parity.
 * The function assumes a system clock frequency of 16 MHz.
 *
 * @param None
 * @return None
 */
void GPS_init(void){
    SYSCTL_RCGCUART_R |= (1<<5); // Enable UART5 clock
    SYSCTL_RCGCGPIO_R |= (1<<4); // Enable GPIOE clock
    while((SYSCTL_PRGPIO_R & (1<<4)) == 0){}; // Wait for GPIOE clock to be ready

    UART5_CTL_R &= ~(1<<0); // Disable UART5

    // Calculate baud rate divisors for 16 MHz system clock and 9600 baud rate
    // BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)
    // UARTSysClk = 16 MHz, ClkDiv = 16, Baud Rate = 9600
    // BRD = 16,000,000 / (16 * 9600) = 104.16667
    // BRDI = integer part of BRD = 104
    // BRDF = fractional part of BRD = 0.16667
    // UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) = 11
    UART5_IBRD_R = 104; // Set integer baud rate divisor
    UART5_FBRD_R = 11; // Set fractional baud rate divisor

    UART5_LCRH_R = 0X0070; // Set line control (8 bits data, 1 stop bit, no parity)
    UART5_CTL_R = 0X0301; // Enable UART5 and its transmitter and receiver
    GPIO_PORTE_AFSEL_R |= (1<<4) | (1<<5); // Enable alternate function for PE4 and PE5
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000; // Configure PE4 and PE5 for UART
    GPIO_PORTE_DEN_R |= 0X30; // Enable digital function for PE4 and PE5
    GPIO_PORTE_AMSEL_R &= ~0X30; // Disable analog function for PE4 and PE5

    GPIO_PORTE_DIR_R |= (1<<5); // Set PE5 as output
    GPIO_PORTE_DIR_R &= ~(1<<4); // Set PE4 as input
}

//////////////////////////////////////////////////////////////////////////////////////////

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
    /*if((UART5_DR_R & 0x00000F00) != 0){
        // Check if there are any errors or if it's a garbage value
        return '\0';
    }*/
    return (char)(UART5_DR_R & 0xFF); // Read the received character from the UART5 data register
}

//////////////////////////////////////////////////////////////////////////////////////////

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
    while(receivedChar != '$'  ){ // Keep reading and storing characters until another '$' character is found
        strGPS[strGPS_counter++] = receivedChar;
        receivedChar = readGPSChar();
    }
    strGPS[--strGPS_counter] = '\0'; // Replace the last '$' character with a null terminator to end the GPS string
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Reads and parses RMC data from a GPS string.
 * This function reads and parses RMC data from a GPS string stored in the global variable strGPS.
 * It extracts and stores the time, latitude, longitude, fixation, and altitude information.
 */
void readRMC(){
    fieldCount = 0;
    token = strtok(strGPS, ","); // Split strGPS into tokens separated by ","
        while (token != NULL) {
            switch (fieldCount) {
                case 1://time
                   // time = token;
                    break;

                case 3: // latitude
                    latitude = dd6m_TO_degree( atof( token ) );
                    break;

                case 4: // north/south
                    if (*token == 'S') {
                       latitude = -1*latitude;
                    }
                    break;

                case 5: // longitude
                    longitude = dd6m_TO_degree( atof( token ) );
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
            token = strtok(NULL, ",");  // Get the next token
        }
}

//////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Calculates the accumulated distance.
 *
 * This function calculates the accumulated distance by adding the distance between the current point and the previous point to the total distance.
 * If this is the first point, it sets the previous latitude and longitude to the current values and returns.
 *
 * @param void
 * @return void
 */
void calcDistAcc(){
    // Check if this is the first point
    if( latPre==0 || lonPre==0 ){
        // Set the previous latitude and longitude to the current values
        latPre=latitude;
        lonPre=longitude;
        return ;
    }
    if(fix == 0){
        return;
    }

    tempDist=calcDistBetween(latPre,lonPre);
    if(tempDist<4){
        return ;
    }
    // Add the distance between the current point and the previous point to the total distance
    totalDist += tempDist;
    // Update the previous latitude and longitude to the current values
    latPre=latitude;
    lonPre=longitude;
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Determines which LED to turn on based on the distance to the end point.
 *
 * This function determines which LED to turn on based on the distance to the end point. If the latitude and longitude are both 0, it turns on all LEDs and returns.
 * Otherwise, it calculates the distance to the end point using the calcDistToEnd function. If the distance is less than 6 meters, it turns on the green LED and sets reached to true.
 * If the distance is less than 6 meters but greater than or equal to 11 meters, it turns on the yellow LED. Otherwise, it turns on the red LED.
 *
 * @param void
 * @return void
 */
void decisionLED(){
    if(latitude == 0 && longitude == 0 ){
        RGB_output(0x0E);
        return;
    }
    if(fix == 0){
        RGB_output(0x0E);
        return;
    }
    double d=calcDistToEnd();
    if(d < 6){ // green on
        RGB_output(0x08);
        reached = true;
    }
    else if(d < 11){ //yellow on
        RGB_output(0x0A);
    }
    else{ //red on
        RGB_output(0x02);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Calculates and displays the direction to the target destination.
 * This function calculates the direction to the target destination based on the current and previous GPS coordinates.
 * It uses vector calculations to determine the angle between the current direction of travel and the direction to the target.
 * It then sets the global variable direction to a string indicating the direction to travel (e.g. "Dirct:Forward", "Dirct:Slight left").
 */
void showDirct() {
    if (fix == 0) {
        return;
    }
    if (fix != 0 && DirctFlag == false) {
        prevLat = latitude; // Set the previous latitude to the current latitude
        prevLong = longitude; // Set the previous longitude to the current longitude
        DirctFlag = true; // Set the direction flag to true
        return;
    }
    if (calcDistBetween(prevLat, prevLong) < 3) {
        return;
    }
    vecDirctLat = latitude - prevLat; // Calculate the change in latitude
    vecDirctLong = longitude - prevLong; // Calculate the change in longitude

    vecLatToEnd = latEnd - latitude; // Calculate the change in latitude to the end point
    vecLongToEnd = lonEnd - longitude; // Calculate the change in longitude to the end point

    // dot product
    dotPdt = vecDirctLat * vecLatToEnd + vecDirctLong * vecLongToEnd;

    // theta
    theta = acos(dotPdt / (absolute(vecDirctLat, vecDirctLong) * absolute(vecLatToEnd, vecLongToEnd))) * 180 / 3.14;

    // cross product
    crossPdt = -vecDirctLat * vecLongToEnd + vecDirctLong * vecLatToEnd;

    if (theta < 10) {
        direction = "Dirct:Forward     ";
    } else if (theta >= 10 && theta <= 80) {
        if (crossPdt > 0)
            direction = "Dirct:Slight left ";
        else
            direction = "Dirct:Slight right";
    } else if (theta > 80 && theta < 100) {
        if (crossPdt > 0)
            direction = "Dirct:Rough left  ";
        else
            direction = "Dirct:Rough right ";
    } else if (theta >= 100 && theta <= 170) {
        if (crossPdt > 0)
            direction = "Dirct:Back left   ";
        else
            direction = "Dirct:Back right  ";
    } else {
        direction = "Dirct:Back   ";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Converts a value in dd6m format to degrees.
 * @param dd6m The value in dd6m format to be converted.
 * @return The converted value in degrees.
 */
double dd6m_TO_degree(double dd6m) {
    int dd = dd6m / 100; // Extract the whole degrees
    double _6m = (dd6m - dd * 100) / 60; // Convert the remaining minutes to degrees
    return dd + _6m; // Return the sum of whole degrees and converted minutes
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if a string is a substring of another string.
 * @param check The string to check if it is a substring.
 * @param string The string to check against.
 * @return True if check is a substring of string, false otherwise.
 */
bool is_substring(char *check, char *string){
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

//////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief Reads and parses GGA data from a GPS string.
 * This function reads and parses GGA data from a GPS string stored in the global variable strGPS.
 * It extracts and stores the time, latitude, longitude, fixation, and altitude information.
 */
void readGGA(){
    fieldCount = 0;
    token = strtok(strGPS, ","); // Split strGPS into tokens separated by ","
        while (token != NULL) {
            switch (fieldCount) {
                case 1://time
                   // time = strcpy (token);
                    break;

                case 2: // latitude
                    latitude = dd6m_TO_degree( atof( token ) );
                    break;

                case 3: // north/south
                    if (*token == 'S') {
                       latitude = -1*latitude;
                    }
                    break;

                case 4: // longitude
                    longitude = dd6m_TO_degree( atof( token ) );
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
            token = strtok(NULL, ",");  // Get the next token
        }
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Reads and parses GLL data from a GPS string.
 * This function reads and parses GLL data from a GPS string stored in the global variable strGPS.
 * It extracts and stores the time, latitude, longitude, fixation, and altitude information.
 */
void readGLL(){
    fieldCount = 0;
    token = strtok(strGPS, ","); // Split strGPS into tokens separated by ","
        while (token != NULL) {
            switch (fieldCount) {
                case 5://time
                //    time = token;
                    break;

                case 1: // latitude
                    latitude = dd6m_TO_degree( atof( token ) );
                    break;

                case 2: // north/south
                    if (*token == 'S') {
                       latitude = -1*latitude;
                    }
                    break;

                case 3: // longitude
                    longitude = dd6m_TO_degree( atof( token ) );
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
            token = strtok(NULL, ","); // Get the next token
        }
}


//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Calculates the magnitude of a 2D vector.
 * @param lat The latitude component of the vector.
 * @param lg The longitude component of the vector.
 * @return The magnitude of the vector.
 */
double absolute(double lat, double lg){
    return sqrt(pow(lat,2)+pow(lg,2));
}
/**
 * @brief Determines the type of NMEA data in a GPS string.
 * This function checks the global variable strGPS to determine the type of NMEA data it contains.
 * It then calls the appropriate function to read and parse the data (readGLL, readRMC, or readGGA).
 */
void NMEA_Type(){
        // check if c1 is a substring of s1, report the results
        if (is_substring(c1,strGPS))
         {
           readGLL();
         }
        else if (is_substring(c2,strGPS))
         {
           readRMC();
         }
        else if(is_substring(c3,strGPS))
        {
           readGGA();
         }
}
