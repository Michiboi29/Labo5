/*
 * lcd_control.h
 *
 *  Created on: 15 nov. 2021
 *      Author: Matheus
 */

#ifndef LCD_CONTROL_H_
#define LCD_CONTROL_H_

#include <macros_utiles.h>
#include "stm32f4xx.h"

#define BIT_RS BIT3
#define BIT_RW BIT4
#define BIT_EN BIT5

#define BIT_D0 BIT0
#define BIT_D1 BIT1
#define BIT_D2 BIT2
#define BIT_D3 BIT3
#define BIT_D4 BIT4
#define BIT_D5 BIT5
#define BIT_D6 BIT6
#define BIT_D7 BIT7

void configureTIM2(float p_frequence);

void configureLcdGPIO(void);
void setLcdBusOutput(void);
void setLcdBusInput(void);
void delay(int cycles);
unsigned char checkBusyFlag(void);
void writeLCD(int p_package);
void instructLCD(int p_package);
void configureLCD(void);

void writeTime(unsigned int p_value);



#endif /* LCD_CONTROL_H_ */
