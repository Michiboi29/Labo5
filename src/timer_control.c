///*
// * lcd_control.c
// *
// *  Created on: 15 nov. 2021
// *      Author: Matheus
// */

#include <timer_control.h>

unsigned int waitCount;
unsigned int monitoringOn = 0;

void configureTIM2(float p_frequence)
{
	volatile int sys_clk = 53760000; //syscoreclk
	volatile int prescaler_1 = 1; // 1 to 512
	volatile int prescaler_2 = 2; // prescaller_2 % prescaler_3 = 4/2 = 2

	RCC->APB1ENR |= BIT0;															// clock enable
	TIM2->CR1 &= ~BIT0;																// clock disable

	TIM2->CR1 &= ~BIT4;																// set as upcounter

	TIM2->DIER |= BIT0;																// peripheral interrupt enable
	NVIC->ISER[0] |= BIT28;															// NVIC timer interrupt enable

	TIM2->PSC = prescaler_1;														// prescaler
	TIM2->ARR = (sys_clk/(prescaler_1*prescaler_2))/(p_frequence);					// set max value (when to interrupt)


	TIM2->CR1 |= BIT7;																// auto-reload preload

	TIM2->CR1 |= BIT0;																// clock start
}

void BoucleDAttente(short Nombre_microseconde_Dattente)
{
	volatile unsigned int keepWaiting = 0;
//	while(keepWaiting <= Nombre_microseconde_Dattente){
//		keepWaiting++;
//		while(waitCount == 0){};
//		waitCount = 0;
//	}
//	while(waitCount <= Nombre_microseconde_Dattente){keepWaiting++;}
//	waitCount = 0;

	for(unsigned int N = 0; N < Nombre_microseconde_Dattente; N++){keepWaiting++;}

}

void setupMonitoring(void)
{
	  // configure les LEDs
	  RCC->AHB1ENR |= BIT3;
	  GPIOD->MODER |= (BIT24 | BIT26 | BIT28); // set mode de input output
	  GPIOD->MODER &= ~(BIT25 | BIT27 | BIT29);

	  monitoringOn = 1;
}
