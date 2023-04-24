#include "init.h"

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
void UART0_init(void){
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
 * @brief Initializes the UART5 peripheral for communication.
 *
 * This function configures the UART5 peripheral
 * for communication using a baud rate of 9600 and 8 data bits, 1 stop bit, and no parity.
 * The function assumes a system clock frequency of 16 MHz.
 *
 * @param None
 * @return None
 */
void UART5_init(void){
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



/**
 * Set the clock frequency of the Tiva TM4C123GLX microcontroller.
 *
 * This function sets the clock frequency of the Tiva TM4C123GLX microcontroller
 * to either 16MHz or 80MHz, depending on the value of the `f` parameter.
 *
 * @param f The desired clock frequency in MHz. Must be either 16 or 80.
 * */
void setCLkFreq(uint8_t f){
    switch (f){
    case 16:
        SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_INT | SYSCTL_MAIN_OSC_DIS);
        break;
    case 80:
        SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    }
/**
 * @brief Initializes the GPIO Port F.
 *
 * Enables the clock for Port F and waits for it to be ready. Unlocks Port F and disables the analog function for pins PF0 to PF4.
 * Allows changes to these pins and sets them to have no alternative function. The direction of PF1, PF2, and PF3 is set to output
 * while the others are set to input. The pins are set to digital and pull-up resistors are enabled for PF0 and PF4. Finally, the LEDs are turned off.
 *
 * @param void
 * @return void
 */
void GPIO_PF_init(void){
  SYSCTL_RCGCGPIO_R |= 0x20;           // enable Clock for portF
  while( (SYSCTL_RCGCGPIO_R&0x20)==0){}// Delay
  GPIO_PORTF_LOCK_R= 0x4C4F434B;       // Unlock portF
  GPIO_PORTF_AMSEL_R &= ~0x1F;         // disable analog function for pf0,pf1,pf2,pf3,pf4
  GPIO_PORTF_CR_R|= 0x1F;              // allow changes for pf0,pf1,pf2,pf3,pf4
  GPIO_PORTF_PCTL_R &= ~0x000FFFFF;    // configure  pf0,pf1,pf2,pf3,pf4 as GPIO
  GPIO_PORTF_AFSEL_R &= ~0x1F;         // no alternative function
  GPIO_PORTF_DIR_R = 0x0E;             // pf1,pf2,pf3: outputs, else inputs
  GPIO_PORTF_DEN_R = 0x1F;             // pf0,pf1,pf2,pf3,pf4: digital
  GPIO_PORTF_PUR_R =0x11;              // pull up resistor enabled for pf0,pf4
  GPIO_PORTF_DATA_R &= 0x0E;           // LEDs are off
}


}
