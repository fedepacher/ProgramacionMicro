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

#define DELAY_40	40

/*=====[Definiciones de tipos de datos publicos]=============================*/

// Tipo de datos que renombra un tipo basico


// Tipo de datos de puntero a funcion


// Tipo de datos enumerado
typedef enum {
	UP, FALLING, DOWN, RISSING,
} button_state;



// Tipo de datos estructua, union o campo de bits
typedef struct {
	gpioMap_t	sw_name;	 /* nombre de la tecla */
	button_state  sw_state; /* estado de la tecla   */
	delay_t 	sw_delay;	/* delay de la tecla presionada para evitar el anti-rebote*/
	INT_16		sw_cont;	/*cuenta la cantidad de veces que fue pulsada */
	INT_16		sw_time_pressed;	/*teimpo de pulsado*/
	bool_t 		sw_pressed;
	bool_t		sw_released;
} buttom_ptr;

/*=====[Prototipos de funciones publicas]====================================*/

void keyInit(buttom_ptr * button, gpioMap_t tecla);

void key_mef_debounce_generic(buttom_ptr * button);

bool_t key_released(buttom_ptr * button);

bool_t key_pressed(buttom_ptr * button);
/*=====[Prototipos de funciones publicas de interrupcion]====================*/



/*=====[C++ fin]=============================================================*/

#ifdef __cplusplus
}
#endif



#endif /* FEDE_CLASE5PM_INC_KEY_GENERIC_H_ */
