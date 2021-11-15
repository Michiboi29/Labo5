/*
 * lcd_control.c
 *
 *  Created on: 15 nov. 2021
 *      Author: Matheus
 */


#include "lcd_control.h"

volatile int lcdInit = 0;

void configureLcdGPIO(void)
{

	// activer clocks des GPIOs B et D
	RCC->AHB1ENR |= BIT1 | BIT3;


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
	instructLCD(0x0E);	// Display control
	writeLCD(0x4D);		// print M
	writeLCD(0x53);		// print S
	writeLCD(0x5F);		// print _
	writeLCD(0x45);		// print E
	writeLCD(0x4D);		// print M
	instructLCD(0xC0);	// 2nd line

    lcdInit = 1;

}
