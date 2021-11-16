/*
 * command.c
 *
 *  Created on: 15 nov. 2021
 *      Author: etienne
 */

#include <command.h>

char readCommand(){
	int p_indx = ptr_read;
	unsigned char cmd = buffer[p_indx++];
	if (p_indx>=20) p_indx = 0;
	unsigned char param = buffer[p_indx++];
	if (p_indx>=20) p_indx = 0;
	unsigned char chk = buffer[p_indx];

	bytesToRead--;
	ptr_read++;
	if (ptr_read>=20) ptr_read = 0;
	if((cmd + param + chk) % 256 != 0){
		return '0';
	}

	if(cmd == 0x41) gereLED(param);
	else if(cmd == 0x42) eraseLCD();
	else if(cmd == 0x43) displayCharLCD(param);

	return '1';
}

void gereLED(uint8_t p_para){
	if(p_para == 0x30){
		GPIOD->ODR &= ~BIT15;
	}
	else if(p_para == 0x31){
		GPIOD->ODR |= BIT15;
	}
}

void eraseLCD(){
	instructLCD(0xC0);	// 2nd line
	for (int i = 0; i < 16; i++)
		writeLCD(0x20); // white space
	position = 0;
}

void displayCharLCD(uint8_t p_para){
	int charPos = 0xC0 + position;
	instructLCD(charPos);	// 2nd line
	writeLCD(p_para);
	position++;
	if(position > 16) position = 16;
}

