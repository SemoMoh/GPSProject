#include "LCD.h"

// Global Variables
extern int fix; // Fixation value (defined in another file) 
extern double latEnd; // Target destination latitude value (defined in another file)
extern double lonEnd; // Target destination longitude value (defined in another file)
extern double longitude; // Longitude value (defined in another file)
extern double latitude; // Latitude value (defined in another file)
extern double totalDist; // Total distance travelled (defined in another file)
extern char *direction ; // Direction to target destination string
extern int fix; // Fixation value (defined in another file) 

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





/**
 * @brief Displays a menu on the LCD display.
 *
 * This function displays a menu on the LCD display by clearing the display,
 * printing a series of strings, and using delays to control the timing of
 * the menu display.
 */
void LCD_Menu() {
    LCD_Clear();
    LCD_PrintByPos(0, 0, "Choose Destination:"); // Print the menu title
    DelaySec(1.5);

    LCD_PrintByPos(1, 0, " Gate 2"); // Print the first menu option
    DelaySec(0.75);

    LCD_PrintByPos(2, 0, " Gate 3"); // Print the second menu option
    DelaySec(0.75);

    LCD_PrintByPos(3, 0, " Gate 6"); // Print the third menu option
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
    LCD_PrintByPos(0, 10, globalArray); // Print the distance to the end point

    // Update Distance Moved
    calcDistAcc(); // Calculate the distance moved
    doubleToString(totalDist);
    LCD_PrintByPos(1, 10, globalArray); // Print the total distance moved

    //Update Direction
    showDirct();
    LCD_PrintLn(2,direction);
}


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
