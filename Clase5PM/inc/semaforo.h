/*
 * semaforo.h
 *
 *  Created on: Mar 18, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_CLASE3PM_INC_SEMAFORO_H_
#define FEDE_CLASE3PM_INC_SEMAFORO_H_


/*==================[inclusiones]============================================*/
#include "led.h"
#include "sapi_datatypes.h"
/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/
#define LED_YELLOW_S	LED1
#define LED_RED_S		LED2
#define LED_GREEN_S		LED3
/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
typedef enum{
	NORMAL = 0,		//modo de funcionamiento del semaforo
	OFFLINE,
	ALARM
} sema_mode_t;


typedef enum{
	RED_S,			//estado semaforo en rojo
	YELLOW_S,		//estado semaforo en amarillo
	GREEN_S			//estado semaforo en verde
} sema_state_t;


typedef struct{
	sema_mode_t mode;	//modo actual
	delay_t delay;		//delay para temporizar cambios en las luces
	sema_state_t state;	//estado de la luz prendida
} semaphore_t;



/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/
/**	"brief 	Funcion inicializa la estructura del semaforo
 *
 * 	@param[in]	pSemaphore		puntero a estructura que contiene al semaforo
 *
 */
bool_t semaphoreInit(semaphore_t * pSemaphore);

/**	"brief 	Funcion controladora del semaforo, indica su funcionamiento normal, offline o alarma
 *
 * 	@param[in]	pSemaphore		puntero a estructura que contiene al semaforo
 *
 */
bool_t semaphore_control(semaphore_t * pSemaphore);

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/





/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif


#endif /* FEDE_CLASE3PM_INC_SEMAFORO_H_ */
