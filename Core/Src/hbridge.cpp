#include "hbridge.hpp"
#include "stm32g0xx_hal.h"

#include <stdint.h>

namespace motors
{
	//Jeep! I start from some global variables ;)
	/*
		DCmin -> 16 bit vairable, if lower DC is set then the motor is stall.
		//Updated when a stall condition is recognised. Will be transfered to RP to memo.
		
		time constant -> how long every change is by default. Slowing down may be faster
	*/
	
	struct {
		uint16_t DCmin;
		uint16_t Tspeedup; //ms
		uint16_t Tslowdown; //ms
		
	} Hparams{DCMINdef,TSUPdef,TSDWdef}; //From the header file
	
	
	
	/*Functions:
	*/
	uint8_t MotorsInit(void)
	{
		//Clocking: //this may modify others code, so bit banding or bit operations are neceserry!
			RCC->APBRSTR2 |= (1<<16);
			RCC->APBRSTR2 &= ~(1<<16);

			RCC->APBENR2 |= (1<<16); //enable timer 15 clock
		//Timer:
			//TIM15->CR2 = 0;
			TIM15->CCMR1 = (6<<12) | (6<<4); //PWM1 modes
			TIM15->ARR = (400-1); // 40kHZ
			//TIM15->RCR -> can be used to automatically change the DC after x states.
			//int only ov | enable 
			TIM15->CR1 = (1<<2) | 1;
		//GPIO:
			RCC->IOPENR |= (1<<1); //enable PORTB clock
			GPIOB->MODER &= ~ ((2<<28) | (2<<30)); //PB15,PB14 alternaive function
			GPIOB->AFR[1] |= (5<<28) | (5<<24);		//AF 5 -> timer ch1 pwm output.
			//BSRR -> to change modes, set has the proiority
			Hparams.DCmin = 60; // -> spróbuj odczytać z RAspberry pi
		return 0; //no testing
	}

	void SetSpeed(uint16_t left,uint16_t right)
	{
		//Of course it wont be so simple :P
		TIM15->CCR1 = left;
		TIM15->CCMR2 = right;
		
		return;
	}
	
}
