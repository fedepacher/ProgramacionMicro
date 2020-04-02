/*
 * semaforo.c
 *
 *  Created on: Mar 18, 2020
 *      Author: fedepacher
 */

#include "semaforo.h"
#include "sapi.h"
#include "key_generic.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

#define INITIAL_DEFAULT_MODE 	NORMAL
#define INITIAL_DEFAULT_STATE 	YELLOW_S

#define TIME_ON_RED		3000
#define TIME_ON_YELLOW	500
#define TIME_ON_GREEN	1000
#define TIME_OFFLINE	500
#define	TIME_ALARM		1000

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
delay_t delay_red;
delay_t delay_yellow;
delay_t delay_green;
delay_t delay_alarm;
delay_t delay_offline;
buttom_ptr but1;
buttom_ptr but2;
buttom_ptr but3;

const char msj_inicial[] = "Inicio de semaforo\r\n";
const char msj_normal[] = "Modo Normal\r\n";
const char msj_alarma[] = "Modo Alarma\r\n";
const char msj_offline[] = "Modo Offline\r\n";

/*=====[Definitions of private global variables]=============================*/
static void semaphore_normal(semaphore_t * sem);
static void semaphore_offline(semaphore_t * sem);	//pasa a modo desconectado prendiendo led amarillo cada 500 mseg
static void semaphore_alarm(semaphore_t * sem);	//pasa a modo alarma prendiendo led rojo y amarillo cada 1 seg
static void semaphore_off();	//apaga todos los leds
static void semaphore_init(semaphore_t * sem);	//inicializa a estado normal la estructura de semaforo

bool_t semaphoreInit(semaphore_t * pSemaphore) {
	//TODO: chequeo de consistencia del puntero
	//TODO: cargar valores iniciales a la estructura
	//TODO:	inicializacion de tiempos de espera de cada luz
	//TODO: devolver verdadero o falso segun corresponda

	bool_t result = FALSE;

	if (NULL == pSemaphore)
		return result;

	//key_init();

	delayInit(&delay_red, TIME_ON_RED);
	delayInit(&delay_yellow, TIME_ON_YELLOW);
	delayInit(&delay_green, TIME_ON_GREEN);
	delayInit(&delay_offline, TIME_OFFLINE);
	delayInit(&delay_alarm, TIME_ALARM);

	semaphore_init(pSemaphore);



	keyInit(&but1, TEC1);
	keyInit(&but2, TEC2);
	keyInit(&but3, TEC3);


	uartInit(UART_USB, 115200);

	uartWriteString(UART_USB, msj_inicial);
	uartWriteString(UART_USB, msj_normal);

	result = TRUE;

	return result;
}

static void semaphore_init(semaphore_t * sem){
	//TODO: inicializacion de estructura semaforo
	sem->mode = INITIAL_DEFAULT_MODE;
	sem->state = INITIAL_DEFAULT_STATE;
	sem->delay = delay_yellow;
}

bool_t semaphore_control(semaphore_t * pSemaphore) {
	//TODO: chequear puntero no sea NULL y que tenga valor valido
	if (NULL == pSemaphore)
		return FALSE;

	//TODO: chequear teclas TEC1,TEC2, TEC3

	key_mef_debounce_generic(&but1);	//hacerlo con un arreglo de puntero
	key_mef_debounce_generic(&but2);
	key_mef_debounce_generic(&but3);

	if (key_released(&but1)) {
		semaphore_init(pSemaphore);
		semaphore_off();
		uartWriteString(UART_USB, msj_normal);
	} else if (key_released(&but2)) {
		pSemaphore->mode = OFFLINE;
		pSemaphore->delay = delay_offline;
		semaphore_off();
		uartWriteString(UART_USB, msj_offline);
	} else if (key_released(&but3)) {
		pSemaphore->mode = ALARM;
		pSemaphore->delay = delay_alarm;
		semaphore_off();
		uartWriteString(UART_USB, msj_alarma);
	}

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
		if (delayRead(&sem->delay)) {
			sem->state = YELLOW_S;
			sem->delay = delay_yellow;
		}
		break;
	case YELLOW_S:
		turnOff(LED_RED_S);
		turnOn(LED_YELLOW_S);
		turnOff(LED_GREEN_S);
		if (delayRead(&sem->delay)) {
			sem->state = GREEN_S;
			sem->delay = delay_green;
		}
		break;
	case GREEN_S:
		turnOff(LED_RED_S);
		turnOff(LED_YELLOW_S);
		turnOn(LED_GREEN_S);
		if (delayRead(&sem->delay)) {
			sem->state = RED_S;
			sem->delay = delay_red;
		}
		break;
	default:

		break;
	}

}

static void semaphore_offline(semaphore_t * sem) {

	if (delayRead(&sem->delay))
		blink(LED_YELLOW_S, TIME_ON_YELLOW);
}

static void semaphore_alarm(semaphore_t * sem) {
	if (delayRead(&sem->delay)) {
		blink(LED_YELLOW_S, TIME_ON_YELLOW);
		blink(LED_RED_S, TIME_ON_YELLOW);
	}
}

static void semaphore_off() {
	turnOff(LED_RED_S);
	turnOff(LED_YELLOW_S);
	turnOff(LED_GREEN_S);
}

