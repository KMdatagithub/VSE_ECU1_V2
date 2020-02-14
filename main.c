/*
 * VSE.c
 *
 * Created: 2/11/2020 6:22:57 PM
 * Author : A_ayman saad
 */ 

#include "gpio.h"
#include "USART.h"
#include "interrupts.h"
#include "led.h"
#include "pushButton.h"
#include "SPI.h"
#define F_CPU 16000000UL
#include <util/delay.h>
volatile uint8_t Speed;
int main(void)
{
	 sei();
	 /*Variables Declaration and initialization*/
	 uint8_t rec_data=0;
	 uint8_t cmd=0;
	 uint8_t BTN_Increase=-1;
	 uint8_t BTN_Decrease=-1;

	 pushButtonInit(BTN_0);
	 pushButtonInit(BTN_1);
	 /*UART Initialization*/
	 USART_CFG_t UART1_CFG;
	 UART1_CFG.CHAR_DATA_NUMBER = USART_8BIT_DATA;
	 UART1_CFG.STOP_BIT_SELECT = USART_1_STOP_BIT;
	 UART1_CFG.USART_BAUD_RATE_SELECT = USART_9600_BAUD_RATE;
	 UART1_CFG.USART_CLOCK_POLARITY = USART_RISING_TRANSMIT;
	 UART1_CFG.USART_MODE = USART_ASYNC_MODE;
	 UART1_CFG.USART_PARITY = USART_PARITY_DIS;
	 UART1_CFG.USART_RX_TX = USART_RX_TX_Enable;
	 UART1_CFG.USART_INTERRUPTS = USART_Interrupt_Disabl;
    USART_Init2(&UART1_CFG);
	 /*SPI Initialization*/
	 SPI_Init(SPI_Master, SPI_CLK_F_64 , SPI_Mode0,LSB_First ,SPI_Interrupts_Disabled);
	 /*Instructions used only once*/
	 UART_Send_String(" Welcome... \n");
	 UART_Send_String(" Please Enter the Initial Speed\n");
	 Speed=USART_Receive_POLLING();
    UART_Send_String("You have entered \n");
	 USART_SEND_POLLING(Speed);
	 SPI_Write(Speed);
	 SPI_Write(Speed);
	 SPI_Write(Speed);
	 
    while (1) 
    {
		  BTN_Increase=pushButtonGetStatus(BTN_0);
		  BTN_Decrease=pushButtonGetStatus(BTN_1);
		  cmd=USART_Receive_POLLING();
		//  if ( BTN_Increase==Pressed)
		  if ( cmd=='+')
		  {
				 Speed++;
				 
				 UART_Send_String(" Speed Incremented New Speed = \n");
				 USART_SEND_POLLING(Speed);
				 SPI_Write(Speed);
				_delay_ms(500);
		  }
		 // if ( BTN_Decrease==Pressed)
		  if ( cmd=='-')
		  {
			  Speed--;
			  if(Speed<'0')
			  {
					Speed='0';
	
			  }
			  else
			  {
					 UART_Send_String(" Speed Decremented New Speed = \n");
					 USART_SEND_POLLING( Speed);
					 SPI_Write(Speed);
			  }
			 
			  _delay_ms(500);
		  }
		  
		 
    }
}

