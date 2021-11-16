/*
 * uart.c
 *
 *  Created on: 14 nov. 2021
 *      Author: Etienne
 */


#include <uart.h>

void configureUART(void)
{
	//PA.0 USART4_TX
	//PA.1 USART4.RX

	RCC->AHB1ENR |=  BIT0; //Give clock to GPIOA

	GPIOA->MODER &= ~BIT0; //  pin 0Alternate function mode
	GPIOA->MODER |= BIT1;

	GPIOA->MODER &= ~BIT2; //  pin1 Alternate function mode
	GPIOA->MODER |= BIT3;

	GPIOA->AFR[0] = BIT3 | BIT7; // Activate the alternate function 8

	RCC ->APB1ENR |=  BIT19; //Give clock to USART4

	UART4->CR1 |= BIT13; //USART enable

	UART4->CR1 &= ~BIT12; // 8 data bits

	UART4->CR1 |= BIT10; // parity control enable

	UART4->CR1 &= ~BIT9; // parrity even

	UART4->CR1 |= BIT3 | BIT2; // receiver and transmitter enable

	UART4->CR1 |= BIT5; // enable interuption at RXNE (RXNEIE)

	UART4->CR2 &= ~(BIT12 | BIT13); // 1 stop bit

	UART4->BRR = (unsigned int)(43.75 * 16); //par calcul scientifique de baud = Fclk/(8*(2-over8)*USARTDIV)

	NVIC->ISER[1] |= BIT20; // position 52 iteruption UART4

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

uint8_t receiveByteUART(void){
	uint8_t return_value;
	while(!(UART4->SR & BIT5));
	return_value = UART4->DR;
	return return_value;
}


