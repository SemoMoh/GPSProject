#ifndef LCD_H_
#define LCD_H_

#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7

#define ROW1    0x80
#define ROW2    0xC0
#define ROW3    0x94
#define ROW4    0xD4


void LCD_init(void);                                //LCD initialization
void LCD_Command(unsigned char c);                  //Send command
void LCD_Show(unsigned char d);                     //Show a char
void LCD_Clear(void);                               //Clear the screen
void LCD_ClearChar(char row, char col);             //Clear specific character from position (row, col)
void LCD_PrintLn(char row, char *s);                //Print specific line from beginning of row
void LCD_PrintByPos(char row, char col, char *s);   //Print specific line from position (row, col)
void LCD_PrintJustify(char i, char *s, char *d);    //Print specific line with 2 texts indented by x
void LCD_Cursor(char row, char col);                //Set cursor
void DelaySec(double s);                            //Delay by (s) seconds / e.g (s=1) -> 1 second
void LCD_Menu();                                    //Menu1: Print gate 2, gate 3 , gate 4
void LCD_ReadDestination();                         //Menu2: Take input from user to pick a specific gate and show details
void LCD_setTargetDestination(int x);               //Menu2: Show target details and waiting state for gps to start fetching
void LCD_ReadDistance();                            //Menu3: Print distance details 
void LCD_UpdateDistance();                          //Menu3: Update values of distance
void LCD_TargetReached();                           //Menu4: Success state and target reached                                

#endif /* LCD_H_ */
