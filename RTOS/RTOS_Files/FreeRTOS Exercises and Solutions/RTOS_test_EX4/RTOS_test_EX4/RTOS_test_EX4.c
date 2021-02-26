/*
 * RTOS_test_EX4.c
 *
 *  At this exercise the UART Rec ISR receive a byte then send it via a message queue to a task that is blocked and waiting for this byte.
 *  This task verifies if this byte is a number (0 to 9), it displays it on seven segment.
                       if not .. it displays (-) sign on seven segment.
 
 
 * 
 *  Author: Nael
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h" // in order to use queue APIs

//============== [Definitions]=============
#define ZERO   0x7E
#define ONE    0x06
#define TWO    0x6D
#define THREE  0x4F
#define FOUR   0x17
#define FIVE   0x5B
#define SIX    0x7B
#define SEVEN  0x0E
#define EIGHT  0x7F
#define NINE   0x5F
#define NOT_NUM   0x01

//================ [Global]================
const unsigned char seven_segment_values[10] = {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE};
static xQueueHandle myQueue;
unsigned char my_data;
	
//================= [ISRs]=================
ISR(USART_RXC_vect)
{	
	//save received data
	my_data = UDR; 
	
	//send data as a message to the queue
	xQueueSendFromISR(myQueue,&my_data,pdTRUE );
		
}

//================ [Functions]=============
void UART_init()
{
	// Note : Clk = 8 MHz
	UCSRA = 0b00000000;
	UCSRB = 0b10010000;    // Rec only with interrupt
	UCSRC = 0b10000110;       // asynchronous mode , No parity , one stop bit , 8 bits
	UBRRH = 0b00000000;
	UBRRL = 51; // baud rate = 9600 bps @ 8MHz
	sei();  // enable global interrupt
}

//=================[Tasks]=================
void UART_2_sevenSegmant (void *pvParameters)
{
	DDRA = 0xff;
	unsigned char rec_data;
	unsigned char ret;
	
	
	 while(1)
	 {
		 //Task will be blocked until a new message is received or timeout.
		 ret = xQueueReceive(myQueue, &rec_data, portMAX_DELAY);
		 
		 if(ret == pdTRUE) // if successfully received a message (not time out)
		 {
			  // Print received byte (no from 0 to 9) in seven segment if the received byte is a number
		    if((rec_data >= '0') && (rec_data<= '9'))
			{
				PORTA = seven_segment_values[rec_data-48]; //ASCII OF '0' = 48
			}
			else // if not a number
			{
				PORTA = NOT_NUM;
			}
			
		 }
	 }
	
}
//================ [Main]==================

int main(void)
{
	// UART initialization
  UART_init();
  
    // Create task
   xTaskCreate( UART_2_sevenSegmant,NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
   
   //Create Queue with size 1
   myQueue = xQueueCreate(1, sizeof(char *));
   
   //Start FreeRTOS
   vTaskStartScheduler();
  
}