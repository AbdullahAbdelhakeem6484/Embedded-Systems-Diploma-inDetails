
/**
* @file My_keypad_driver.h
* @brief keypad driver for ATMEGA16.  
* @author Islam Mohamed.
*/

#include"My_keypad.h"
#include"macros.h"
#include <avr/io.h>
#include <util/delay.h>

unsigned char return_val=NOT_PRESSED;
unsigned char row_index;
unsigned char column_index;
unsigned char row_val=NOT_PRESSED; 
unsigned char keys_matrix[4][4]={{'7','8','9','/0'},{'4','5','6','/0'},{'1','2','3','/0'},{'/0','0','/0','/0'}};

/****************************keypad initialization**************************/

void keypad_init(void){


	DDRA=0xf0; // set port A (a0 to a3 as input ) (a4 to a7 as output )
	PORTA=0xff; // activate pull-up resistors from a0 to a3 and out a4 to a7 '1'


}

unsigned char getPressed(void){
	
	for(column_index=0;column_index<4;column_index++)
	{
		CLR_BIT(PORTA,(column_index+4)); // activate  column
		
		_delay_ms(10); // wait for 10 miliseconds 
		
		// check if any key is pressed 
		
	
		
				
		if((PINA & 0x0f ) != 0x0f)
		{
			 
			row_val=PINA &0x0F;
		
			while((PINA & 0x0f) != 0x0f ); //  single press logic 
			//SET_BIT(PORTA,(column_index+4)); 
			break;
		
		}	 	
		
		SET_BIT(PORTA,(column_index+4)); // deactivate selected column	

	}
	
	switch (row_val)
	{
	
		case FIRST_ROW:
			row_index=0;

		break;

		case SECOND_ROW:
			row_index=1; 

		break;

		case THIRD_ROW:
			row_index=2;

		break;

		case FOURTH_ROW:
			row_index=3;

		break;
		

	}
	
	if(row_val==NOT_PRESSED) 
	{
		return_val=NOT_PRESSED;
	}
	else
	{
		return_val= keys_matrix[row_index][column_index]; // get value of key from keys matrix
		
		row_val=NOT_PRESSED; 
	}
	
	return return_val;
}
