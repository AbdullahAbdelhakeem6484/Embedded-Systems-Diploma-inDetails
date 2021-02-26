/*
 * RTOS_LAB3_ATMEGA32.c
 *
 * Created: 1/31/2014 12:45:52 AM
 *  Author: medhat
 */ 

#include <avr/io.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "my_keypad.h"
#include "lcd_4bit.h"

#define F_CPU 8000000UL
#include <util/delay.h>

/*define tasks priority*/
#define KEYPAD_TASK_PR		2U
#define LCD_TASK_PR		1U

/*Tasks functions prototypes */
void KeypadTask (void * pvParameters);
void LcdTask (void * pvParameters);

/*create Message Queue Handle*/
xQueueHandle buffer;

int main(void)
{
    /*init LCD Driver*/
	lcd_init();
	
	/*init Keypad driver */
	keypad_init();
	
	/*create message queue */
	
	buffer = xQueueCreate(6,sizeof(unsigned char));
	
	/*create LCD task*/
	xTaskCreate(LcdTask,"LcdTask",configMINIMAL_STACK_SIZE,NULL,LCD_TASK_PR,NULL);	
	
	/*create KeyPad Task*/
	xTaskCreate(KeypadTask,"KeypadTask",configMINIMAL_STACK_SIZE,NULL,KEYPAD_TASK_PR,NULL);
	
	/*start OS*/
	vTaskStartScheduler();
	
}

/*keypad task function it is a periodic task with period = 50 ms  */
void KeypadTask( void * pvParameters )
{
	/*variable used to hold value of pressed key */
	unsigned char val; 
	
	for (;;)
	{
		/*get pressed key value*/
		val=getPressed();
		/*check if no key pressed*/
		if (val != NOT_PRESSED)
		{
			/*if a key is pressed send the value to buffer" message queue"*/
			xQueueSend(buffer,&val,portMAX_DELAY);
		}
		/*delay to make task a periodic task every 50 ms */
		vTaskDelay(50);
	}
}

/*LCD task function that responsible about printing buffer content*/
void LcdTask( void * pvParameters )
{
	unsigned char val;
	unsigned char ret;
	static unsigned char counter=0;
	for (;;)
	{
		
		ret = xQueueReceive(buffer,&val,portMAX_DELAY);
		
		if(ret==pdTRUE)
		{
			counter++;
			if (counter>6)
			{
				lcd_clrScreen();
				lcd_dispString("wait");
			}
			else
			{
				lcd_displayChar(val);				
			}
		}		
			
	}
}
