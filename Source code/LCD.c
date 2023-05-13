#include "LCD.h"

// Global variables
bool nearReachedFlag = false; // Flag used to indicate that the message has been displayed.
bool startMenuFlag = false;   // flag to know if the the start menu is used or not
char globalArray[10]; // Global array of characters, used to convert a number into a string

// Functions

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the LCD display.
 *
 * This function enables the LCD peripheral, sets the GPIO pins as outputs,
 * and sends a series of commands to initialize the LCD display.
 */
void LCD_init() {
    // Enable the LCD peripheral
    SysCtlPeripheralEnable(LCDPORTENABLE);
    // Set the LCD pins as output
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

    // Delay
    SysCtlDelay(50000);

    // Set the RS pin to low
    GPIOPinWrite(LCDPORT, RS, 0x00);

    // Write 0x30 to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, 0x30);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    // Delay
    SysCtlDelay(50000);

    // Write 0x30 to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, 0x30);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    // Delay
    SysCtlDelay(50000);

    // Write 0x30 to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, 0x30);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    // Delay
    SysCtlDelay(50000);

    // Write 0x20 to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, 0x20);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    // Delay
    SysCtlDelay(50000);

    LCD_Command(0x0F); // Turn on Lcd
    LCD_Clear(); // Clear screen
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Sends a command's to the LCD display.
 *
 * @param c The command's hexadecimal value to send to the LCD display.
 *
 * This function sends a command to the LCD display by setting the appropriate
 * GPIO pins and using delays to ensure proper timing.
 */
void LCD_Command(unsigned char c) {
    // Write the upper nibble of the command to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0));
    // Set the RS pin to low
    GPIOPinWrite(LCDPORT, RS, 0x00);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);

    // Delay
    SysCtlDelay(50000);

    // Set the enable pin to low
    GPIOPinWrite(LCDPORT, E, 0x00);

    // Delay
    SysCtlDelay(50000);

    // Write the lower nibble of the command to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4);
    // Set the RS pin to low
    GPIOPinWrite(LCDPORT, RS, 0x00);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);

    // Delay
    SysCtlDelay(10);

    // Set the enable pin to low
    GPIOPinWrite(LCDPORT, E, 0x00);

    // Delay
    SysCtlDelay(50000);
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Displays a character on the LCD display.
 *
 * @param d The character to display on the LCD display.
 *
 * This function displays a character on the LCD display by setting the appropriate
 * GPIO pins and using delays to ensure proper timing.
 */
void LCD_Show(unsigned char d) {
    // Write the upper nibble of the data to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0));
    // Set the RS pin to high
    GPIOPinWrite(LCDPORT, RS, 0x01);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);

    // Delay
    SysCtlDelay(10);
    // Set the enable pin to low
    GPIOPinWrite(LCDPORT, E, 0x00);

    // Delay
    SysCtlDelay(50000);

    // Write the lower nibble of the data to the data pins
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4);
    // Set the RS pin to high
    GPIOPinWrite(LCDPORT, RS, 0x01);
    // Send data to LCD
    GPIOPinWrite(LCDPORT, E, 0x02);

    // Delay
    SysCtlDelay(10);

     // Set the enable pin to low
     GPIOPinWrite(LCDPORT,E ,0x00);

     // Delay
     SysCtlDelay(50000);
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Clears the LCD display.
 *
 * This function clears the LCD display
 */
void LCD_Clear(void) {
    LCD_Command(0x01); // Clear the display
    SysCtlDelay(10); // Delay
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Prints a string on a specified row of the LCD display.
 *
 * @param row The row on which to print the string.
 * @param s The string to print on the LCD display.
 *
 * This function prints a string on a specified row of the LCD display by
 * setting the cursor position and calling the LCD_Show function for each
 * character in the string.
 */
void LCD_PrintLn(char row, char *s) {
    LCD_Cursor(row, 0); // Set the cursor to the specified row and first column
    int i;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == '\0') {
            break;
        }
        LCD_Show(s[i]); // Display the character
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Prints a string at a specified position on the LCD display.
 *
 * @param row The row on which to print the string (0 to 3).
 * @param col The column at which to start printing the string (0 to 19).
 * @param s The string to print on the LCD display.
 *
 * This function prints a string at a specified position on the LCD display by
 * setting the cursor position and calling the LCD_Show function for each
 * character in the string.
 */
void LCD_PrintLnByPos(char row, char col, char *s) {
    LCD_Cursor(row, col); // Set the cursor to the specified row and column
    int i;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == '\0') {
            break;
        }
        LCD_Show(s[i]); // Display the character
    }
}

//////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief Clears a character at a specified position on the LCD display.
 *
 * @param row The row of the character to clear.
 * @param col The column of the character to clear.
 *
 * This function clears a character at a specified position on the LCD display by
 * setting the cursor position and displaying a space character.
 */
void LCD_ClearChar(char row, char col) {
    LCD_Cursor(row, col); // Set the cursor to the specified row and column
    LCD_Show(' '); // Display a space character
    LCD_Cursor(row, col); // Set the cursor back to the specified row and column
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Delays execution for a specified number of seconds.
 *
 * @param s The number of seconds to delay execution.
 *
 * This function delays execution for a specified number of seconds by calling
 * the SysCtlDelay function with an appropriate argument.
 */
void DelaySec(double s) {
    SysCtlDelay(s * (16000000 / 3));
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Sets the cursor position on the LCD display.
 *
 * @param row The row of the cursor position.
 * @param col The column of the cursor position.
 *
 * This function sets the cursor position on the LCD display by sending the
 * appropriate command to the LCD display based on the row and column arguments.
 */
void LCD_Cursor(char row, char col) {
    switch (row) {
        case 0:
            LCD_Command(ROW1 + (col % 16)); // Set cursor to first row
            break;
        case 1:
            LCD_Command(ROW2 + (col % 16)); // Set cursor to second row
            break;
        case 2:
            LCD_Command(ROW3 + (col % 16)); // Set cursor to third row
            break;
        case 3:
            LCD_Command(ROW4 + (col % 16)); // Set cursor to fourth row
            break;
        default:
            LCD_Command(ROW4 + (col % 16)); // Set cursor to fourth row by default
    }
}
//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Sets the target destination and displays it on the LCD display.
 *
 * @param x The index of the target destination.
 *
 * This function sets the target destination based on the value of the x argument,
 * (value related to each gate), displays the latitude and longitude of the target 
 * destination on the LCD display, and attempts to establish a GPS connection. 
 * The function displays the status of the GPS connection on the LCD display.
 */
void LCD_setTargetDestination(int x) {
    if (x == 1) {
        /*Gate 2 */
        latEnd = 30.0646014; // Set the destination latitude
        lonEnd = 31.2773738; // Set the destination longitude
        LCD_PrintLnByPos(1, 0, "lat: 30.0646014"); // Print the destination latitude
        LCD_PrintLnByPos(2, 0, "long: 31.2773738"); // Print the destination longitude
        LCD_PrintLnByPos(3, 0, "Status: Starting..."); // Print the status
        //wait for signal
        while (fix == 0) {
            //read till fix = 1 (signal is found)
            readGPSString();
            NMEA_Type();
        }
        LCD_PrintLnByPos(3, 0, "Status: Connected."); // Update the status
        DelaySec(2);
    } else if (x == 2) {
        /*Gate 3 */
        latEnd = 30.063907; // Set the destination latitude
        lonEnd = 31.2776239; // Set the destination longitude
        LCD_PrintLnByPos(1, 0, "lat: 30.063907"); // Print the destination latitude
        LCD_PrintLnByPos(2, 0, "long: 31.2776239"); // Print the destination longitude
        LCD_PrintLnByPos(3, 0, "Status: Starting..."); // Print the status
        //wait for signal
        while (fix == 0) {
            //read till fix = 1 (signal is found)
            readGPSString();
            NMEA_Type();
        }
        LCD_PrintLnByPos(3, 0, "Status: Connected."); // Update the status
        DelaySec(2);
    } else {
        /*Gate 6*/
        latEnd = 30.064828; // Set the destination latitude
        lonEnd = 31.280305; // Set the destination longitude
        LCD_PrintLnByPos(1, 0, "lat: 30.064828"); // Print the destination latitude
        LCD_PrintLnByPos(2, 0, "long: 31.280305"); // Print the destination longitude
        LCD_PrintLnByPos(3, 0, "Status: Starting..."); // Print the status
        //wait for signal
        while (fix == 0) {
            //read till fix = 1 (signal is found)
            readGPSString();
            NMEA_Type();
        }
        LCD_PrintLnByPos(3, 0, "Status: Connected."); // Update the status
        DelaySec(2);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Reads and displays the distance information on the LCD display.
 *
 * This function reads and displays the distance information on the LCD display
 * by calling various functions to calculate the distance to the end point and
 * the total distance moved.
 */
void LCD_ReadDistance() {
    LCD_Clear();
    // print_Current_Position();

    LCD_PrintLn(0, "DistToEnd:");
    doubleToString(calcDistToEnd());
    LCD_PrintLnByPos(0, 10, globalArray); // Print the distance to the end point


    calcDistAcc(); // Calculate the distance moved
    LCD_PrintLn(1, "DistMoved:");
    doubleToString(totalDist);
    LCD_PrintLnByPos(1, 10, globalArray); // Print the total distance moved

    LCD_PrintLn(2,direction);
}
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Displays a menu on the LCD display.
 *
 * This function displays a menu on the LCD display by clearing the display,
 * printing a series of strings, and using delays to control the timing of
 * the menu display.
 */
void LCD_DestinationMenu() {
    LCD_Clear();
    LCD_PrintLnByPos(0, 0, "Choose Destination:"); // Print the menu title
    DelaySec(1.5);

    LCD_PrintLnByPos(1, 0, " Gate 2"); // Print the first menu option
    DelaySec(0.75);

    LCD_PrintLnByPos(2, 0, " Gate 3"); // Print the second menu option
    DelaySec(0.75);

    LCD_PrintLnByPos(3, 0, " Gate 6"); // Print the third menu option
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Reads the user's destination selection from the LCD display.
 *
 * This function reads the user's destination selection from the LCD display by
 * monitoring the state of two input switches. The function displays a cursor on
 * the LCD display to indicate the current selection and updates the cursor position
 * based on the state of the input switches. When the user makes a selection, the
 * function calls the LCD_setTargetDestination function with the appropriate argument
 * and exits.
 */
void LCD_ReadDestination() {
    bool flag = true;
    uint8_t i = 1;
    uint8_t p = 1;
    while (flag) {
        // Read input
        if (!sw1_input() && sw2_input()) {
            LCD_ClearChar(p, 0); // Clear the character at the specified position
            LCD_Cursor(i, 0); // Move the cursor to the specified row
            LCD_Show('>'); // Display the '>' character
            p = i;
            i++;
            SysCtlDelay((1200000 / 3)); // Delay for 400ms
            if (i > 3) {
                i = 1;
            }
        } else if (sw1_input() && !sw2_input()) {
            switch (p) {
                case 1:
                    LCD_Clear();
                    LCD_PrintLn(0, "Gate 2:"); // Print the selected destination
                    flag = false;
                    LCD_setTargetDestination(p); // Set the target destination
                    break;
                case 2:
                    LCD_Clear();
                    LCD_PrintLn(0, "Gate 3:"); // Print the selected destination
                    flag = false;
                    LCD_setTargetDestination(p); // Set the target destination
                    break;
                case 3:
                    LCD_Clear();
                    LCD_PrintLn(0, "Gate 6:"); // Print the selected destination
                    flag = false;
                    LCD_setTargetDestination(p); // Set the target destination
                    break;
            }
        } else {
            continue;
        }
    }

    DelaySec(2);
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Updates the distance information on the LCD display.
 *
 * This function updates the distance information on the LCD display by calling
 * various functions to calculate the distance to the end point and the total
 * distance moved.
 */
void LCD_UpdateDistance() {
    // Update Remaining Distance
    doubleToString(calcDistToEnd());
    LCD_PrintLnByPos(0, 10, globalArray); // Print the distance to the end point

    // Update Distance Moved
    calcDistAcc(); // Calculate the distance moved
    doubleToString(totalDist);
    LCD_PrintLnByPos(1, 10, globalArray); // Print the total distance moved

    //Update Direction
    showDirct();
    LCD_PrintLn(2,direction);
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Displays the target reached menu on the LCD display.
 *
 * This function updates the distance information on the LCD display by calling
 * various functions to calculate the distance to the end point and the total
 * distance moved.
 */
void LCD_TargetReachedMenu() {
    LCD_Clear();
    LCD_PrintLn(0, "Target Reached ;)");
    LCD_PrintLn(2, "DistMoved: "); // Print "DistanceMoved:"
    calcDistAcc(); // Calculate the distance moved
    doubleToString(totalDist);
    LCD_PrintLnByPos(2, 10, globalArray); // Print the total distance moved
}

//////////////////////////////////////////////////////////////////////////////////////////
// decision functions

/**
 * @brief Displays the start menu on the LCD display.
 *
 * This function displays the start menu on the LCD display by printing a welcome
 * message, calling the LCD_DestinationMenu function to display the menu, and calling various
 * functions to read GPS data and update the LCD display. The function also sets
 * a flag to indicate that the start menu has been displayed.
 */
void startMenu() {
    LCD_PrintLn(0, "Welcome to miniGPS."); // Print welcome message
    DelaySec(2);
    LCD_DestinationMenu(); // Display menu

    // Get data from GPS
    readGPSString();
    NMEA_Type();
    decisionLED();

    LCD_ReadDestination(); // Read destination from user input
    startMenuFlag = true;
    LCD_ReadDistance(); // Display distances
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Displays a message on the LCD display when the target destination is reached.
 *
 * This function displays a message on the LCD display when the target destination is
 * reached by calling various functions to update the LCD display and entering an
 * infinite loop to prevent further execution.
 */
void targetReached() {
    decisionLED();
    LCD_TargetReachedMenu(); // Display target reached message
    while (1) {}
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Updates the distance information during a trip.
 *
 * This function updates the distance information during a trip by calling various
 * functions to read GPS data, update the LCD display, and control an LED based on
 * the distance to the target destination.
 */
bool fixFlag = false;
void trip() {
    // Get new data from GPS
    readGPSString();
    NMEA_Type();
    decisionLED();

    while(fix == 0 || latitude > 40 || latitude < 20 || longitude >40 || longitude < 20){
        LCD_Clear();
        LCD_PrintLn(1,"  !! No signal !!");
        readGPSString();
        NMEA_Type();
        decisionLED();
         if(latitude > 20 && latitude < 40 && longitude >20 && longitude < 40){
             LCD_Clear();
             LCD_ReadDistance(); // Display distances
             if(nearReachedFlag == true){
                 LCD_PrintLn(3, "Your target is near."); // Print message
                 DelaySec(2);
             }
         }
    }
    LCD_UpdateDistance(); // Update the displayed distances
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Displays a message on the LCD display when near the target destination.
 *
 * This function displays a message on the LCD display when near the target destination
 * by calling various functions to update the distance information and checking a flag
 * to determine whether to display the message. The function sets a flag to indicate
 * that the message has been displayed.
 */
void nearReached() {
    trip();
    if (nearReachedFlag == false) {
        LCD_PrintLn(3, "Your target is near."); // Print message
        LCD_PrintLn(2, "                   ");
        DelaySec(2);
        nearReachedFlag = true;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Converts a double value to a string and stores it in the globalArray.
 * @param value The double value to be converted.
 * @return void
 */
void doubleToString(double value) {
    int integerPart = (int)value; // Get the integer part of the value
    double decimalPart = value - integerPart; // Get the decimal part of the value
    int index = 0;
    int k = 0;

    // Convert the integer part to string
    while (integerPart > 0) {
        globalArray[index++] = '0' + integerPart % 10;
        integerPart /= 10;
    }

    // Reverse the string
    for (k = 0; k < (index / 2); k++) {
        char temp = globalArray[k];
        globalArray[k] = globalArray[index - k - 1];
        globalArray[index - k - 1] = temp;
    }

    // Add the decimal point
    globalArray[index++] = '.';

    // Convert the decimal part to string
    for (k = 0; k < 3; k++) {
        decimalPart *= 10;
        int digit = (int)decimalPart;
        globalArray[index++] = '0' + digit;
        decimalPart -= digit;
    }

    // Add the null terminator
    globalArray[index] = '\0';
}
