/**
* @file myfile.h
* @brief header file of keypad driver for ATMEGA16.  
* @author Islam Mohamed.
*/

#ifndef MY_KEYPAD_H_
#define MY_KEYPAD_H_

void keypad_init(void);
unsigned char getPressed(void);

#define FIRST_ROW 0x0e
#define SECOND_ROW 0x0d
#define THIRD_ROW 0x0b
#define FOURTH_ROW 0x07
#define NOT_PRESSED 0xff

#endif  

