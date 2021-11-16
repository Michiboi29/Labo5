/*
 * lcd_control.c
 *
 *  Created on: 15 nov. 2021
 *      Author: Matheus
 */


#include "lcd_control.h"

volatile unsigned int lcdInit = 0;
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
	TIM2->ARR = (sys_clk/(prescaler_1*prescaler_2))/(p_frequence);				// set max value (when to interrupt)

	NVIC->ISER[0] |= BIT28;															// NVIC timer interrupt enable

	TIM2->CR1 |= BIT7;																// auto-reload preload

	TIM2->CR1 |= BIT0;																// clock start
}

void configureLcdGPIO(void)
{

	// activer clocks des GPIOs B, D et timer 2
	RCC->AHB1ENR |= BIT1 | BIT3;
	RCC->APB1ENR |= BIT0;

	// configurer pins instruction LCD output
	GPIOB->MODER |= BIT6 | BIT8 | BIT10;
	GPIOB->MODER &= ~(BIT7 | BIT9 | BIT11);

	//configurer pins donnees LCD output
	setLcdBusOutput();

}

void setLcdBusOutput(void)
{
	// mettre bus en monde sortie
	GPIOD->MODER |= BIT0 | BIT2 | BIT4 | BIT6 | BIT8 | BIT10 | BIT12 | BIT14;
	GPIOD->MODER &= ~(BIT1 | BIT3 | BIT5 | BIT7 | BIT9 | BIT11 | BIT13 | BIT15);
}

void setLcdBusInput(void)
{
	// mettre bus en monde sortie
	GPIOD->MODER &= ~(BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 | BIT8 | BIT9 | BIT10 | BIT11 | BIT12 | BIT13 | BIT14 | BIT15);
}

void delay(int cycles){
	for(volatile int wait_var = 0; wait_var < cycles; wait_var++){}
}

unsigned char checkBusyFlag(void)
{
	setLcdBusInput();

	GPIOB->ODR |= (BIT_EN | BIT_RW);	// Enable ON, RS to high
	GPIOB->ODR &= ~BIT_RS;
	
	unsigned char result = (GPIOD->IDR & BIT_D7);
	
	return result;
}

void writeLCD(int p_package)
{
	setLcdBusOutput();

	GPIOB->ODR |= (BIT_EN | BIT_RS);	// Enable ON, RS to high
	GPIOB->ODR &= ~BIT_RW;

	GPIOD->ODR = (GPIOD->ODR & 0xFFFFFF00) | (p_package & 0xFF);		//print p_package


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

void writeTime(unsigned int p_value)
{
	instructLCD(0x8A);	// set cursor
//	instructLCD(0x14);	// set left shift
	setLcdBusOutput();

	unsigned int intValue = p_value;

	for(int i = 0; i <= 4;i++)
	{
		int value = intValue % 10;
		intValue /= 10;

		GPIOB->ODR |= (BIT_EN | BIT_RS);	// Enable ON, RS to high
		GPIOB->ODR &= ~BIT_RW;

		GPIOD->ODR = (GPIOD->ODR & 0xFFFFFF00) | ((value + '0') & 0xFF);		//print toSend value


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

//	instructLCD(0x10);	// set right shift
}

void instructLCD(int p_package)
{
	setLcdBusOutput();

	GPIOB->ODR &= ~(BIT_RS | BIT_RW); //RS and RW to 0
	GPIOB->ODR |= BIT_EN;	// Enable ON

	GPIOD->ODR = (GPIOD->ODR & 0xFFFFFFF00) | (p_package & 0xFF);		//print p_package


	delay(100);
	GPIOB->ODR &= ~BIT_EN;	// Enable OFF
	GPIOB->ODR |= (BIT_RS | BIT_RW);

    unsigned char flag = 0;
    if(lcdInit = 0){delay(10000);}
    else{flag = checkBusyFlag();}

    while (flag)
    {
        flag = checkBusyFlag();
    }
    
	
}

void configureLCD(void)
{
	//INITI SEQ.

	for(int iter = 0; iter < 4; iter++)
	{
		instructLCD(0x38);
	}

	instructLCD(0x01);	// Display clear
	instructLCD(0x0E);	// Display control (0x0C to erase cursor)
	writeLCD(0x4D);		// print M
	writeLCD(0x53);		// print S
	writeLCD(0x5F);		// print _
	writeLCD(0x45);		// print E
	writeLCD(0x4D);		// print M
	instructLCD(0xC0);	// 2nd line

    lcdInit = 1;

}
