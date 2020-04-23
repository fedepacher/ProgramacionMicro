/*
 * key_generic.c
 *
 *  Created on: Apr 1, 2020
 *      Author: fedepacher
 */

/*=====[Inclusion de su propia cabecera]=====================================*/

#include "../../SubscribeMQTT/inc/key_generic.h"

/*=====[Inclusiones de dependencias de funciones privadas]===================*/



/*=====[Macros de definicion de constantes privadas]=========================*/



/*=====[Macros estilo funcion privadas]======================================*/



/*=====[Definiciones de tipos de datos privados]=============================*/

// Tipo de datos que renombra un tipo basico


// Tipo de datos de puntero a funcion


// Tipo de datos enumerado


// Tipo de datos estructua, union o campo de bits


/*=====[Definiciones de Variables globales publicas externas]================*/



/*=====[Definiciones de Variables globales publicas]=========================*/



/*=====[Definiciones de Variables globales privadas]=========================*/



/*=====[Prototipos de funciones privadas]====================================*/



/*=====[Implementaciones de funciones publicas]==============================*/

void keyInit(button_ptr * button, gpioMap_t tecla){
	button->sw_state = SW_ESTADO_INICIAL;
	button->sw_name = tecla;
	button->sw_pressed = FALSE;
	button->sw_released = FALSE;
	button->sw_tick_cont	= 0;
	button->sw_time_pressed = 0;
}


void key_mef_debounce_generic(button_ptr * button) {

		switch (button->sw_state) {
		case UP:
			button->sw_pressed = FALSE;
			button->sw_released = FALSE;
			if (!gpioRead(button->sw_name)) {
				button->sw_state = FALLING;
				button->sw_time_pressed = 0;
				//tickInit( 1 );		//setea base de tiempo a 1 msg// Adentro de configInit del main llama a tickInit(1);
				tickWrite(0);		//pone a celo la base de tiempo para contar cuanot tiempo esta presionado, en configinit del main esta
				delayInit(&button->sw_delay, DELAY_ANTIREBOTE);
			}

			break;
		case FALLING:
			if (delayRead(&button->sw_delay)) {
				if (!gpioRead(button->sw_name)) {
					button->sw_state = DOWN;
					button->sw_pressed = TRUE;
				}
				else
					button->sw_state = UP;
			}
			break;
		case DOWN:
 			if (gpioRead(button->sw_name)) {
				button->sw_state = RISSING;
				delayInit(&button->sw_delay, DELAY_ANTIREBOTE);
			}

			break;
		case RISSING:
			if (delayRead(&button->sw_delay)) {
				if (gpioRead(button->sw_name)) {
					button->sw_state = UP;
					button->sw_time_pressed = tickRead();
					button->sw_released = TRUE;
				}
				else
					button->sw_state = UP;
			}
			break;
		default:

			break;
		}


}

bool_t key_released(button_ptr * button){

	return button->sw_released;
}

bool_t key_pressed(button_ptr * button){

	return button->sw_pressed;
}

tick_t key_time_pressed(button_ptr * button){
	return button->sw_time_pressed;
}

/*=====[Implementaciones de funciones de interrupcion publicas]==============*/

