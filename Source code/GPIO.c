#include "GPIO.h"


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

/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Outputs data to the RGB LEDs.
 *
 * This function outputs the given data to the RGB LEDs. It resets the RGB LEDs and then turns on the needed LEDs based on the given data.
 *
 * @param data The data to be output to the RGB LEDs.
 * @return void
 */
void RGB_output(unsigned char data){
  GPIO_PORTF_DATA_R &= ~0x0E;         // reset RGP LEDs
  if (data !=0){
    GPIO_PORTF_DATA_R |= data;        // needed LEDs are on
  }}


/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Reads the input from switch 1 (PF4).
 *
 * This function reads the input from switch 1 (PF4) and returns 1 if the switch is not pushed and 0 if it is pushed.
 *
 * @param void
 * @return bool Returns 1 if the switch is not pushed and 0 if it is pushed.
 */
bool sw1_input(void){
  switch(GPIO_PORTF_DATA_R & 0x10){
    case 0x10:
      return 1;                       // 1 for not pushed
    default:
      return 0;                       // 0 for pushed
  }
}

/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Reads the input from switch 0 (PF0).
 *
 * This function reads the input from switch 2 (PF0) and returns 1 if the switch is not pushed and 0 if it is pushed.
 *
 * @param void
 * @return unsigned char Returns 1 if the switch is not pushed and 0 if it is pushed.
 */
bool sw2_input(void){
    switch(GPIO_PORTF_DATA_R & 0x01){
    case 0x01:
      return 1;                       // 1 for not pushed
    default:
      return 0;                       // 0 for pushed
  }
}

