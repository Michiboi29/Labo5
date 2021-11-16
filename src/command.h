/*
 * command.h
 *
 *  Created on: 15 nov. 2021
 *      Author: etienne
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <macros_utiles.h>
#include "stm32f4xx.h"
#include <lcd_control.h>

extern int ptr_read;
extern int position;

char readCommand();

void gereLED(uint8_t p_para);
void eraseLCD();
void displayCharLCD(uint8_t p_para);

#endif /* COMMAND_H_ */
