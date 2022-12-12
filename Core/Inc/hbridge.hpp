/*
TIM15 @ 16MHz
F PWM = 40kHz (T = 25us)
Max cmp value 400 is 7V on the motors
*/

#include "stm32g0xx_hal.h"

#ifndef HBRIDGE_HPP
#define HBRIDGE_HPP

#define DCMINdef (uint16_t)60 //minimal duty cycle per motor -> start value
#define TSUPdef (uint16_t)100 //time for DC to ramp up   (ms)
#define TSDWdef (uint16_t)100 //time for DC to ramp down (ms)

namespace motors
{

	uint8_t MotorsInit(void); 
	//set the timer, gpios

	void SetSpeed(uint16_t left,uint16_t right); //move indefinately, lspeed, rspeed
	//what about the influence of batteries?
	
}

#endif
