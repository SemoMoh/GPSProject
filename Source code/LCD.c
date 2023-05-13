#include "LCD.h"

// Global Variables
extern int fix; // Fixation value (defined in another file) 
// Functions
//////////////////////////////////////////////////////////////////////////////////////////









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
