/*
 * led.h
 *
 *  Created on: Mar 18, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_CLASE3PM_INC_LED_H_
#define FEDE_CLASE3PM_INC_LED_H_

/*=====[Inclusions of private function dependencies]=========================*/
#include "sapi.h"
/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
typedef gpioMap_t lamp_t;
/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/
/**	"brief 	Funcion que enciende el correspondiente led
 *
 * 	@param[in]	lamp	led a encender
 *
 */
void turnOn(lamp_t lamp);

/**	"brief 	Funcion que apaga el correspondiente led
 *
 * 	@param[in]	lamp	led a apagar
 *
 */
void turnOff(lamp_t lamp);

/**	"brief 	Funcion que enciende y apaga el correspondiente led
 *
 * 	@param[in]	lamp	led a encender/apagar
 *
 * 	@param[in]	blinkTime	tiempo a encender/apagar
 *
 */
void blink(lamp_t lamp, tick_t blinkTime);
/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/





#endif /* FEDE_CLASE3PM_INC_LED_H_ */
