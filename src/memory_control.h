/*
 * memory_control.h
 *
 *  Created on: 14 nov. 2021
 *      Author: Etienne
 */

#ifndef MEMORY_CONTROL_H_
#define MEMORY_CONTROL_H_

#include "stm32f4xx.h"
#include "macros_utiles.h"

void configureUART(void);
void sendByteUART(uint8_t p_byte);
void sendStringUART(const char * p_string);
uint8_t receiveByteUART(void);


#endif /* MEMORY_CONTROL_H_ */
