/*
 * semaforo.c
 *
 *  Created on: Mar 18, 2020
 *      Author: fedepacher
 */

#include "semaforo.h"
#include "sapi.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

#define INITIAL_DEFAULT_MODE 	NORMAL
#define INITIAL_DEFAULT_STATE 	YELLOW_S

#define TIME_ON_RED		3000
#define TIME_ON_YELLOW	500
#define TIME_ON_GREEN	1000

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
delay_t delay_red;
delay_t delay_yellow;
delay_t delay_green;


/*=====[Definitions of private global variables]=============================*/
static void semaphore_normal(semaphore_t * sem);
static void semaphore_offline(semaphore_t * sem);
static void semaphore_alarm(semaphore_t * sem);



bool_t semaphoreInit(semaphore_t * pSemaphore) {
	//TODO: chequeo de consistencia del puntero
	//TODO: cargar valores iniciales a la estructura
	//TODO:	inicializacion de tiempos de espera de cada luz
	//TODO: devolver verdadero o falso segun corresponda

	bool_t result = FALSE;

	if (NULL == pSemaphore)
		return result;

	pSemaphore->mode = INITIAL_DEFAULT_MODE;
	pSemaphore->state = INITIAL_DEFAULT_STATE;

	delayInit(&delay_red, TIME_ON_RED);
	delayInit(&delay_yellow, TIME_ON_YELLOW);
	delayInit(&delay_green, TIME_ON_GREEN);



	result = TRUE;

	return result;
}

bool_t semaphore_control(semaphore_t * pSemaphore) {
	//TODO: chequear puntero no sea NULL y que tenga valor valido
	if (NULL == pSemaphore)
		return FALSE;

	//TODO: chequear teclas TEC1,TEC2, TEC3
	if (!gpioRead(TEC1))
		pSemaphore->mode = NORMAL;
	else if (!gpioRead(TEC2))
		pSemaphore->mode = OFFLINE;
	else if (!gpioRead(TEC3))
		pSemaphore->mode = ALARM;

	//TODO: ejecutar funcion de modo normal, offline, alarm
	switch (pSemaphore->mode) {
	case NORMAL:
		semaphore_normal(pSemaphore);
		break;
	case OFFLINE:
		semaphore_offline(pSemaphore);
		break;
	case ALARM:
		semaphore_alarm(pSemaphore);
		break;

	default:
		break;
	}

	return TRUE;
}
/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

static void semaphore_normal(semaphore_t * sem) {

	//TODO: funcionamiento normal

	switch (sem->state) {
	case RED_S:
		turnOn(LED_RED_S);
		turnOff(LED_YELLOW_S);
		turnOff(LED_GREEN_S);
		if (delayRead(&delay_red)) {
			sem->state = YELLOW_S;
		}
		break;
	case YELLOW_S:
		turnOff(LED_RED_S);
		turnOn(LED_YELLOW_S);
		turnOff(LED_GREEN_S);
		if (delayRead(&delay_yellow)) {
			sem->state = GREEN_S;
		}
		break;
	case GREEN_S:
		turnOff(LED_RED_S);
		turnOff(LED_YELLOW_S);
		turnOn(LED_GREEN_S);
		if (delayRead(&delay_green)) {
			sem->state = RED_S;
		}
		break;
	default:

		break;
	}

}

static void semaphore_offline(semaphore_t * sem) {

	blink(LED_YELLOW_S, TIME_ON_YELLOW);
}

static void semaphore_alarm(semaphore_t * sem) {
	blink(LED_YELLOW_S, TIME_ON_YELLOW);
	blink(LED_RED_S, TIME_ON_YELLOW);
}

