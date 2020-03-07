/*
 * board_ext.h
 *
 *  Created on: Mar 6, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_TRABAJO1_EJERCICIO1_V1_INC_BOARD_EXT_H_
#define FEDE_TRABAJO1_EJERCICIO1_V1_INC_BOARD_EXT_H_


/*==================[inclusiones]============================================*/
#include "sapi_datatypes.h"

/*==================[c++]====================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
typedef enum{
	BOARD_LED_ID_1 = 0,
	BOARD_LED_ID_2,
	BOARD_LED_ID_3,
	BOARD_LED_ID_TOTAL
}board_led_id_enum;

typedef enum{
	BOARD_SW_ID_1 = 0,
	BOARD_SW_ID_2,
	BOARD_SW_ID_3,
	BOARD_SW_ID_4,
	BOARD_SW_ID_TOTAL
}board_sw_id_enum;

typedef enum{
	BOARD_LED_MSG_OFF = 0,
	BOARD_LED_MSG_ON,
	BOARD_LED_MSG_TOGGLE
}board_led_msg_enum;

/*==================[tipos de datos declarados por el usuario]===============*/

/*==================[declaraciones de datos externos]========================*/

/*==================[declaraciones de funciones externas]====================*/

/**	"brief 	Funcion que setea el led indicado
 * 	@param[in]	id		id del led a encender
 * 	@param[in]	msg		accion a ejecutar por el led
 */
void board_setLed(board_led_id_enum id, board_led_msg_enum msg);

/**	@brief	Devuelve el estado del pulsador
 *
 * 	@param[in]	id		id del pulsador
 * 	@return	true	si el pulsador esta apretado
 * 			false	si el pulsador no esta apretado
 */
bool_t board_getSw(board_sw_id_enum id);

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif


#endif /* FEDE_TRABAJO1_EJERCICIO1_V1_INC_BOARD_EXT_H_ */
