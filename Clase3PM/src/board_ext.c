/*
 * board_ext.c
 *
 *  Created on: Mar 6, 2020
 *      Author: fedepacher
 */

#include "board_ext.h"		// su propia biblioteca

#include "sapi.h"        // <= Biblioteca sAPI

/*=================================[Declaraciones internas]=====================================*/

static const gpioMap_t board_gpioSw[] = {
		TEC1, TEC2, TEC3, TEC4
};

bool_t board_getSw(board_sw_id_enum id){

	return !gpioRead( board_gpioSw[id] );
}

