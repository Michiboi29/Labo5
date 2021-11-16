/*
 * lcd_control.c
 *
 *  Created on: 15 nov. 2021
 *      Author: Matheus
 */

#include "timer_control.h"

volatile unsigned int timerValue = 0; 

void TIM2_IRQHandler(void)
{
	if(timerValue == 99999)
	{
		timerValue = 0;
	} else {
		++timerValue;
	}
}

void configureTIM2(float p_frequence)
{
	volatile int sys_clk = 53760000;
	volatile int prescaler_1 = 500;
	volatile int prescaler_2 = 2;

	TIM2->CR1 &= ~BIT0;																// clock start

	RCC->APB1ENR |= BIT0;															// clock enable
	TIM2->CR1 &= ~BIT4;																// set as upcounter

	TIM2->DIER |= BIT0;																// peripheral interrupt enable

	TIM2->PSC = prescaler_1;														// prescaler
	TIM2->ARR = (sys_clk/(prescaler_1*prescaler_2))/(p_frequence);					// set max value (when to interrupt)

	NVIC->ISER[0] |= BIT28;															// NVIC timer interrupt enable

	TIM2->CR1 |= BIT7;																// auto-reload preload

	TIM2->CR1 |= BIT0;																// clock start
}

void writeTime(unsigned int p_value)
{
	instructLCD(0x8F);	// set cursor
	instructLCD(0x06);	// set left shift
	setLcdBusOutput();

	unsigned int intValue = p_value;

	for(int i = 0; i <= 4;i++)
	{
		int value = intValue % 10;
		intValue /= 10;

		GPIOB->ODR |= (BIT_EN | BIT_RS);	// Enable ON, RS to high
		GPIOB->ODR &= ~BIT_RW;

		if (value)
		{
			GPIOD->ODR = (GPIOD->ODR & 0xFFFFFF00) | ((value + '0') & 0xFF);		//print toSend value
		} else {
			GPIOD->ODR = (GPIOD->ODR & 0xFFFFFF00) | ((' ') & 0xFF);				//print toSend value
		}

		delay(100);
		GPIOB->ODR &= ~BIT_EN;	// Enable OFF
		GPIOB->ODR &= ~BIT_RS;
		GPIOB->ODR |= BIT_RW;

		unsigned char flag = 0;
		if(lcdInit = 0){delay(10000);}
		else{flag = checkBusyFlag();}

		while (flag)
		{
			flag = checkBusyFlag();
		}
	}

	instructLCD(0x04);	// set right shift
}
