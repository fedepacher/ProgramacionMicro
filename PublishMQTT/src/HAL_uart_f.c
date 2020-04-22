/*
 * HAL_uart_f.c
 *
 *  Created on: Apr 15, 2020
 *      Author: fedepacher
 */

/*=====[Inclusion of own header]=============================================*/

#include "HAL_uart_f.h"


/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/


void HAL_uart_f_Init( uartMap_t uart, uint32_t baudRate ){

	uartConfig(uart, baudRate);
}

void HAL_uart_f_WriteString( uartMap_t uart, const char* str )
{
	uartWriteString(uart, str);
}

bool_t HAL_uart_f_ReadByte( uartMap_t uart, uint8_t* receivedByte )
{

   return uartReadByte(uart, receivedByte);
}

void HAL_uart_f_WriteByte( uartMap_t uart, const uint8_t value )
{
	uartWriteByte(uart, value);
}


void HAL_uart_f_WriteByteArray( uartMap_t uart, const uint8_t* byteArray, uint32_t byteArrayLen ){
	uartWriteByteArray(uart, byteArray, byteArrayLen);
}


