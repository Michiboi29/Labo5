/*
 * command.c
 *
 *  Created on: 15 nov. 2021
 *      Author: etienne
 */

#include <command.h>

char readCommand(uint8_t p_buffer[20]){
	unsigned char cmd = p_buffer[ptr_read];
	ptr_read ++;
	if (ptr_read>=20) ptr_read = 0;
	unsigned char para = p_buffer[ptr_read];
	ptr_read ++;
	if (ptr_read>=20) ptr_read = 0;
	unsigned char chk = p_buffer[ptr_read];
	ptr_read ++;
	if (ptr_read>=20) ptr_read = 0;

	if((cmd + para + chk) % 256 == 0){
		return '1';
	}

	return '0';
}

void gereLED(uint8_t p_para){

}

void eraseLCD(){
	instructLCD(0xC0);	// 2nd line
	for (int i = 0; i < 16; i++)
		writeLCD(0x20); // white space
	instructLCD(0xC0);	// 2nd line
}

void displayCharLCD(uint8_t p_para){
	int charPos = 0xC0 + position;
	instructLCD(charPos);	// 2nd line
	writeLCD(p_para);
	position++;
	if(position > 16) position = 16;
}

