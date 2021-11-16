/*
 * uart.h
 *
 *  Created on: 14 nov. 2021
 *      Author: Etienne
 */

#ifndef UART_H_
#define UART_H_

#include <macros_utiles.h>
#include "stm32f4xx.h"

void configureUART(void);
void sendByteUART(uint8_t p_byte);
void sendStringUART(const char * p_string);
uint8_t receiveByteUART(void);


#endif /* UART_H_ */
