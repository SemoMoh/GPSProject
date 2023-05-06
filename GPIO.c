#include "GPIO.h"
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
