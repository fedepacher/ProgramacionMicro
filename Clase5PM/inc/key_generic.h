/*
 * key_generic.h
 *
 *  Created on: Apr 1, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_CLASE5PM_INC_KEY_GENERIC_H_
#define FEDE_CLASE5PM_INC_KEY_GENERIC_H_

#include "sapi.h"

/*=====[C++ comienzo]========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Macros de definicion de constantes publicas]=========================*/

//#define PI 3.14

/*=====[Macros estilo funcion publicas]======================================*/

#define DELAY_ANTIREBOTE	40		/*tiempo del antirebote*/
#define SW_ESTADO_INICIAL		UP			/*estado inicial del pulsador*/

/*=====[Definiciones de tipos de datos publicos]=============================*/

// Tipo de datos que renombra un tipo basico


// Tipo de datos de puntero a funcion


// Tipo de datos enumerado
typedef enum {
	UP, FALLING, DOWN, RISSING,		/*estados de la MEF*/
} button_state;



// Tipo de datos estructua, union o campo de bits
typedef struct {
	gpioMap_t		sw_name;	 /* nombre de la tecla */
	button_state  	sw_state; /* estado de la tecla   */
	delay_t 		sw_delay;	/* delay de la tecla presionada para evitar el anti-rebote*/
	tick_t			sw_tick_cont;	/*cuenta la cantidad de veces que fue pulsada */
	INT_16			sw_time_pressed;	/*tiempo de pulsado*/
	bool_t 			sw_pressed;			/*indica si fue presionado*/
	bool_t			sw_released;		/*indica si fue soltado*/
} button_ptr;

/*=====[Prototipos de funciones publicas]====================================*/

/**
 * @brief	Rutina que inicializa los pulsadores
 * @param[in]	button		pasa un puntero a la estructura de borones
 * @param[in]	tecla		pasa el nombre de la tecla
 *
 * @return	true	si el pulsador fue pulsado y liberado
 * 			false	si el pulsador no fue pulsado
 */
void keyInit(button_ptr * button, gpioMap_t tecla);

/**
 * @brief	Rutina que chequea estado de pulsador aplicando antirebote con MEF
* @param[in]	button		pasa un puntero a la estructura de botones
 */
void key_mef_debounce_generic(button_ptr * button);

/**
 * @brief	Rutina que chequea si una tecla fue presionada y soltada
 * @param[in]	button		pasa un puntero a la estructura de botones
 *
 * @return	true	si el pulsador fue pulsado y liberado
 * 			false	si el pulsador no fue pulsado
 */
bool_t key_released(button_ptr * button);

/**
 * @brief	Rutina que chequea si una tecla fue presionada
 * @param[in]	button		pasa un puntero a la estructura de borones
 *
 * @return	true	si el pulsador fue liberado
 * 			false	si el pulsador no fue pulsado
 */
tick_t key_time_pressed(button_ptr * button);
/*=====[Prototipos de funciones publicas de interrupcion]====================*/



/*=====[C++ fin]=============================================================*/

#ifdef __cplusplus
}
#endif



#endif /* FEDE_CLASE5PM_INC_KEY_GENERIC_H_ */
