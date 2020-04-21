/*
 * esp8266_io.h
 *
 *  Created on: Apr 15, 2020
 *      Author: fedepacher
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ESP8266_IO_H
#define __ESP8266_IO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "sapi.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DEFAULT_TIME_OUT                 3000 /* in ms */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

 /* Private functions ---------------------------------------------------------*/



 /**
  * @brief  ESP8266 IO Initalization.
  *         This function inits the UART interface to deal with the esp8266,
  *         then starts asynchronous listening on the RX port.
  * @param None
  * @retval 0 on success, -1 otherwise.
  */
int8_t ESP8266_IO_Init(void);

/**
 * @brief  ESP8266 IO Deinitialization.
 *         This function Deinits the UART interface of the ESP8266. When called
 *         the esp8266 commands can't be executed anymore.
 * @param  None.
 * @retval None.
 */
void ESP8266_IO_DeInit(void);

/**
 * @brief  Send Data to the ESP8266 module over the UART interface.
 *         This function allows sending data to the  ESP8266 WiFi Module, the
 *          data can be either an AT command or raw data to send over
 a pre-established WiFi connection.
 * @param pData: data to send.
 * @param Length: the data length.
 * @retval 0 on success, -1 otherwise.
 */
int8_t ESP8266_IO_Send(uint8_t* Buffer, uint32_t Length);

/**
 * @brief  Receive Data from the ESP8266 module over the UART interface.
 *         This function receives data from the  ESP8266 WiFi module, the
 *         data is fetched from a ring buffer that is asynchonously and continuously
 filled with the received data.
 * @param  Buffer: a buffer inside which the data will be read.
 * @param  Length: the Maximum size of the data to receive.
 * @retval int32_t: the actual data size that has been received.
 */
int32_t ESP8266_IO_Receive(uint8_t* Buffer, uint32_t Length);

#ifdef __cplusplus
}
#endif

#endif /* __ESP8266_IO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
