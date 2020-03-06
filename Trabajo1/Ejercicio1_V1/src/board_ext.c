/*
 * board_ext.c
 *
 *  Created on: Mar 6, 2020
 *      Author: fedepacher
 */

#include "board_ext.h"		// su propia biblioteca
#include "sapi.h"        // <= Biblioteca sAPI

/*=================================[Declaraciones internas]=====================================*/
static const gpioMap_t board_gpioLeds[] = {
		LED1, LED2, LED3
};


static const gpioMap_t board_gpioSw[] = {
		TEC1, TEC2, TEC3, TEC4
};


void board_setLed(board_led_id_enum id, board_led_msg_enum msg){

	switch(msg){
		case BOARD_LED_MSG_OFF:
			gpioWrite(board_gpioLeds[id], OFF);
		break;

		case BOARD_LED_MSG_ON:
			gpioWrite(board_gpioLeds[id], ON);
			break;

		case BOARD_LED_MSG_TOGGLE:
			gpioToggle(board_gpioLeds[id]);
			break;

		default:
			break;
	}
}

bool_t board_getSw(board_sw_id_enum id){

	return !gpioRead( board_gpioSw[id] );
}

