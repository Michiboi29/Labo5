/*
 * memory_control.c
 *
 *  Created on: 14 nov. 2021
 *      Author: Etienne
 */


#include "memory_control.h"

void configureUART(void)
{
	//PA.0 USART4_TX
	//PA.1 USART4.RX

	/*****Setup the pins*****/
	RCC->AHB1ENR |=  BIT0; //Give clock to GPIOA

	GPIOA->MODER &= ~BIT0; //  PA.0 Alternate function mode
	GPIOA->MODER |= BIT1;

	GPIOA->MODER &= ~BIT2; //  PA.1 Alternate function mode
	GPIOA->MODER |= BIT3;

	GPIOA->AFR[0] = BIT3 | BIT7; // Activate the alternate function 8 (UART4) for PA.0 and PA.1 (voir table 9 de la datasheet)
	/*****End setup the pins*****/


	/*****Setup the UART*****/
	RCC ->APB1ENR |=  BIT19; //Give clock to USART4

	UART4->CR1 &= ~BIT12; // 8 data bits

	UART4->CR1 |= BIT3 | BIT2; // receiver and transmitter enable

	UART4->CR2 &= ~(BIT12 | BIT13); // 1 stop bit

	UART4->BRR = (unsigned int)(7.29 * 16); // Formule page 978 du users guide: baud = Fclk/(8*(2-over8)*USARTDIV) ici Fclk est divisé par 4

	UART4->CR1 |= BIT13; //USART enable
	/*****End setup the UART*****/

}


void sendByteUART(uint8_t p_byte)
{
	while(!(UART4->SR & BIT6));
	UART4->DR = p_byte;
}

void sendStringUART(const char * p_string)
{
	volatile int i = 0;
	while(p_string[i] != '\0')
		sendByteUART(p_string[i++]);
}

unsigned int receiveByteUART(){
	unsigned int return_value;
	while((UART4->SR & BIT5) == 0x0);
	return_value = UART4->DR;
	return return_value;
}
