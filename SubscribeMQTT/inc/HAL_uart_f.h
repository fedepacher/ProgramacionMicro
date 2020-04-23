/*
 * HAL_uart_f.h
 *
 *  Created on: Apr 15, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_MEF_CONN_WIFI_INC_HAL_UART_F_H_
#define FEDE_MEF_CONN_WIFI_INC_HAL_UART_F_H_

/*=====[Avoid multiple inclusion - begin]====================================*/

#include "sapi.h"

/*=====[Inclusions of public function dependencies]==========================*/

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

/**
 * @brief  Initialize the UART
 * @param  uart: UART
 * @param  baudRate: speed
 */
void HAL_uart_f_Init( uartMap_t uart, uint32_t baudRate );

/**
 * @brief  Send string to the uart
 * @param  uart: UART
 * @param  baudRate: lenght of the string to be sent
 */
void HAL_uart_f_WriteString( uartMap_t uart, const char* str );

/**
 * @brief  Read string to the uart
 * @param  uart: UART
 * @param  receivedByte: byte received.
 */
bool_t HAL_uart_f_ReadByte( uartMap_t uart, uint8_t* receivedByte );

/**
 * @brief  Send byte to the uart
 * @param  uart: UART
 * @param  value: byte to be sent.
 */
void HAL_uart_f_WriteByte( uartMap_t uart, const uint8_t value );


/**
 * @brief  Send byte array to the uart. Blocking
 * @param  uart: UART
 * @param  byteArray: byte array.
 * @param  byteArrayLen: lenght of the byte array.
 */
void HAL_uart_f_WriteByteArray( uartMap_t uart, const uint8_t* byteArray, uint32_t byteArrayLen );
/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* FEDE_MEF_CONN_WIFI_INC_HAL_UART_F_H_ */
