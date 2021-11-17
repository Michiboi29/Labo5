///*
// * timer_control.h
// *
// *  Created on: 15 nov. 2021
// *      Author: Matheus
// */

#ifndef TIMER_CONTROL_H_
#define TIMER_CONTROL_H_

#include <macros_utiles.h>
#include "stm32f4xx.h"

void configureTIM3(float p_frequence);
void BoucleDAttente(short Nombre_microseconde_Dattente);
void setupMonitoring(void);

#endif /* TIMER_CONTROL_H_ */
