/*
 * led.c
 *
 *  Created on: Mar 18, 2020
 *      Author: fedepacher
 */
#include "../../SubscribeMQTT/inc/led.h"

#include "sapi.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/
void turnOn(lamp_t lamp){
	gpioWrite(lamp, ON);
}

void turnOff(lamp_t lamp){
	gpioWrite(lamp, OFF);
}

void blink(lamp_t lamp){

	/*static delay_t delay;
	delayInit(&delay, blinkTime);

	if(delayRead(&delay))*/
		gpioToggle(lamp);
}

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/


