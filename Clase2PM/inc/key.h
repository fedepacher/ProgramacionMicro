/*
 * key.h
 *
 *  Created on: Mar 6, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_TRABAJO1_EJERCICIO1_V1_INC_KEY_H_
#define FEDE_TRABAJO1_EJERCICIO1_V1_INC_KEY_H_

/*==================[inclusions]=============================================*/
#include "../../Clase2PM/inc/board_ext.h"
#include "board.h"

/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions definition]==========================*/
/**	@brief	Rutina que inicializa un arreglo de pulsadores
 *
 */
void key_init(void);

/**	@brief	Rutina que indica si un boton fue pulsado
 *
 * 	@param[in]	id 		posicion en el vector contenedor de pulsadores
 *
 */
bool key_getPressEv(board_sw_id_enum id);

/**	@brief	Rutina que se chequea periodicamente cada 1ms para determinar si se produjo un evento en los pulsadores
 *
 */
void key_periodicTask1ms(void);


/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/


#endif /* FEDE_TRABAJO1_EJERCICIO1_V1_INC_KEY_H_ */
