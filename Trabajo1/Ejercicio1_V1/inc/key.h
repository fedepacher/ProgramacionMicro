/*
 * key.h
 *
 *  Created on: Mar 6, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_TRABAJO1_EJERCICIO1_V1_INC_KEY_H_
#define FEDE_TRABAJO1_EJERCICIO1_V1_INC_KEY_H_

/*==================[inclusions]=============================================*/
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
void key_init(void);
bool key_getPressEv(board_sw_id_enum id);
void key_periodicTask1ms(void);


/*==================[cplusplus]==============================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/


#endif /* FEDE_TRABAJO1_EJERCICIO1_V1_INC_KEY_H_ */
