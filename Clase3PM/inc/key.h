/*
 * key.h
 *
 *  Created on: Mar 19, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_CLASE3PM_INC_KEY_H_
#define FEDE_CLASE3PM_INC_KEY_H_


#include "board.h"
#include "board_ext.h"

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


#endif /* FEDE_CLASE3PM_INC_KEY_H_ */
