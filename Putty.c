#include "Putty.h"

/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initializes the UART0 peripheral for communication, it will be used to send data to PC.
 *
 * This function configures the UART0 peripheral
 * for communication using a baud rate of 9600 and 8 data bits, 1 stop bit, and no parity.
 * The function assumes a system clock frequency of 16 MHz.
 *
 * @param None
 * @return None
 */
void Putty_init(void){
    SYSCTL_RCGCUART_R |= (1<<0); // Enable UART0 clock
    SYSCTL_RCGCGPIO_R |= (1<<0); // Enable GPIOA clock
    while((SYSCTL_PRGPIO_R & (1<<0)) == 0){}; // Wait for GPIOA clock to be ready

    UART0_CTL_R &= ~(1<<0); // Disable UART0

    // Calculate baud rate divisors for 16 MHz system clock and 9600 baud rate
    // BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)
    // UARTSysClk = 16 MHz, ClkDiv = 16, Baud Rate = 9600
    // BRD = 16,000,000 / (16 * 9600) = 104.16667
    // BRDI = integer part of BRD = 104
    // BRDF = fractional part of BRD = 0.16667
    // UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5) = 11
    UART0_IBRD_R = 104; // Set integer baud rate divisor
    UART0_FBRD_R = 11; // Set fractional baud rate divisor

    UART0_LCRH_R = 0X0070; // Set line control (8 bits data, 1 stop bit, no parity)
    UART0_CTL_R = 0X0301; // Enable UART0 and its transmitter and receiver
    GPIO_PORTA_AFSEL_R |= (1<<0) | (1<<1); // Enable alternate function for PA0 and PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011; // Configure PA0 and PA1 for UART
    GPIO_PORTA_DEN_R |= 0X03; // Enable digital function for PA0 and PA1
    GPIO_PORTA_AMSEL_R &= ~0X03; // Disable analog function for PA0 and PA1

    GPIO_PORTA_DIR_R |= (1<<1); // Set PA1 as output
    GPIO_PORTA_DIR_R &= ~(1<<0); // Set PA0 as input
}


/**
 * @brief Transmits a single character using UART0.
 *
 * This function transmits a single character using the UART0 peripheral.
 * The function waits until the UART0 transmit FIFO is not full before writing
 * the character to the UART0 data register.
 *
 * @param c The character to transmit.
 * @return None
 */
void printChar(uint8_t c){
    while (UART0_FR_R & (1<<5)){}; // Wait until the UART0 transmit FIFO is not full
    UART0_DR_R = c; // Write the character to the UART0 data register to transmit it
}



/**
 * @brief Transmits a string using UART0.
 *
 * This function transmits a null-terminated string using the UART0 peripheral.
 * . The function calls the printChar function to transmit
 * each character in the string. A newline character is transmitted at the end of the string.
 *
 * @param str The null-terminated string to transmit.
 * @return None
 */
void printString(char * str){
    // Loop until the end of the string is reached
    while(*str != 0){
        // Transmit the current character using the printChar function
        printChar(*str);
        // Move to the next character in the string
        str++;
    }
    // Transmit a newline character at the end of the string
   printChar('\r');
   printChar('\n');
   printChar('\r');

}
