///*
// * lcd_control.c
// *
// *  Created on: 15 nov. 2021
// *      Author: Matheus
// */
//
//#include "timer_control.h"
//
//
//void configureTIM2(float p_frequence)
//{
//	volatile int sys_clk = 53760000; //syscoreclk
//	volatile int prescaler_1 = 500; // 1 to 512
//	volatile int prescaler_2 = 2; // prescaller_2 % prescaler_3 = 4/2 = 2
//
//	RCC->APB1ENR |= BIT0;															// clock enable
//	TIM2->CR1 &= ~BIT0;																// clock disable
//
//	TIM2->CR1 &= ~BIT4;																// set as upcounter
//
//	TIM2->DIER |= BIT0;																// peripheral interrupt enable
//	NVIC->ISER[0] |= BIT28;															// NVIC timer interrupt enable
//
//	TIM2->PSC = prescaler_1;														// prescaler
//	TIM2->ARR = (sys_clk/(prescaler_1*prescaler_2))/(p_frequence/1000);					// set max value (when to interrupt)
//
//
//	TIM2->CR1 |= BIT7;																// auto-reload preload
//
//	TIM2->CR1 |= BIT0;																// clock start
//}
//
//void writeTime(unsigned int p_value)
//{
//	instructLCD(0x8F);	// set cursor
//	instructLCD(0x04);	// set left shift
//	setLcdBusOutput();
//
//	unsigned int intValue = p_value;
//
//	for(int i = 0; i <= 4;i++)
//	{
//		int value = intValue % 10;
//		intValue /= 10;
//
//		writeLCD(value + '0');
//	}
//
//	instructLCD(0x06);	// set right shift
//}
