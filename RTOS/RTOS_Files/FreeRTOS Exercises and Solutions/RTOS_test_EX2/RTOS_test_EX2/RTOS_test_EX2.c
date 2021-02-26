/*
 * RTOS_test_EX2.c
 *
 * The same as EX1 but using just one body function. We had to use the task argument (*pv) in order make more diffetent tasks
 * LED_blink_data stuct is created to pass different arguments to the task function.
 *
 *  Author: Nael
 */ 


#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
//==================[Global]===============
typedef struct{
	
	 unsigned char pin_no;
	 unsigned int led_delay;
		
	}LED_blink_data;
	
// create LED stucts
LED_blink_data led1;
LED_blink_data led2;
	
//================= [Tasks] ===============

void Blink_task( void *pv)
{
	unsigned char pin_number;
	unsigned int dly;
	
	 // cast the pv pointer into "LED_blink_data" struct datatype and access it's elements
	 pin_number = (*((LED_blink_data*)pv)).pin_no;
	 dly        = (*((LED_blink_data*)pv)).led_delay;
	 
	DDRA |=(1<<pin_number); //PA.pin_number is output
	
	while(1)
	{
		
		PORTA ^= (1<<pin_number); //toggle PA.pin_number
		vTaskDelay(dly); //OS Delay
	}
}



//================= [Main] ====================
#include <avr/io.h>

int main(void)
{
	
	//initialize led1 and led2 structs 
	led1.pin_no = 0;
	led1.led_delay = 200;
	led2.pin_no = 6;
	led2.led_delay = 1000;
	
	
	
	// Create Tasks
	xTaskCreate( Blink_task,NULL, configMINIMAL_STACK_SIZE+10, &led1, 1, NULL );
	xTaskCreate( Blink_task,NULL, configMINIMAL_STACK_SIZE+10, &led2, 2, NULL );
	
	// Start FreeRTOS
	vTaskStartScheduler();
	
}