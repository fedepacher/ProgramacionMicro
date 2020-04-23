/*
 * esp8266_io.h
 *
 *  Created on: Apr 15, 2020
 *      Author: fedepacher
 */

/* Includes ------------------------------------------------------------------*/
#include "../../SubscribeMQTT/inc/esp8266_io.h"

#include "../../SubscribeMQTT/inc/HAL_uart_f.h"
#include "../../SubscribeMQTT/inc/main.h"
#include "sapi.h"

/* Private define ------------------------------------------------------------*/
#define RING_BUFFER_SIZE	(1024 * 2)

/* Private typedef -----------------------------------------------------------*/
typedef struct {
	uint8_t data[RING_BUFFER_SIZE];
	uint16_t tail;
	uint16_t head;
} RingBuffer_t;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RingBuffer_t WiFiRxBuffer;
//UART_HandleTypeDef WiFiUartHandle;

/* Private function prototypes -----------------------------------------------*/
static void WIFI_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Rx Callback when new data is received on the UART.
 * @param  UartHandle: Uart handle receiving the data.
 * @retval None.
 */

void HAL_UART_RxCpltCallback(void *nada) {
	/* If ring buffer end is reached reset tail pointer to start of buffer */
	if (++WiFiRxBuffer.tail >= RING_BUFFER_SIZE) {
		WiFiRxBuffer.tail = 0;
	}

	char c = uartRxRead(UART_USB);
	printf("Recibimos <<%c>> por UART\r\n", c);

	//HAL_UART_Receive_IT(UartHandle, (uint8_t *)&WiFiRxBuffer.data[WiFiRxBuffer.tail], 1);
}


int8_t ESP8266_IO_Init(void) {
	/* Set the WiFi USART configuration parameters */

	/* Inicializar la UART_USB junto con las interrupciones de Tx y Rx */
	HAL_uart_f_Init(UART_USB, 115200);
	HAL_uart_f_Init(UART_232, 115200);
	// Seteo un callback al evento de recepcion y habilito su interrupcion
	//uartCallbackSet(UART_USB, UART_RECEIVE, HAL_UART_RxCpltCallback, NULL);
	// Habilito todas las interrupciones de UART_USB
	//uartInterrupt(UART_USB, true);

	/* Once the WiFi UART is intialized, start an asynchrounous recursive
	 listening. the HAL_UART_Receive_IT() call below will wait until one char is
	 received to trigger the HAL_UART_RxCpltCallback(). The latter will recursively
	 call the former to read another char.  */
	WiFiRxBuffer.head = 0;
	WiFiRxBuffer.tail = 0;

	//HAL_UART_Receive_IT(&WiFiUartHandle, (uint8_t *)&WiFiRxBuffer.data[WiFiRxBuffer.tail], 1);

	return 0;
}


void ESP8266_IO_DeInit(void) {
	/* Reset USART configuration to default */
	//HAL_UART_DeInit(&WiFiUartHandle);
}


int8_t ESP8266_IO_Send(uint8_t* pData, uint32_t Length) {
	/* Unlike the ESP8266_IO_Receive(), the ESP8266_IO_Send() is using a blocking call
	 to ensure that the AT commands were correctly sent. */
	int8_t ret = 0;

	HAL_uart_f_WriteByteArray(UART_232, pData, Length);


	return ret;
}


int32_t ESP8266_IO_Receive(uint8_t* Buffer, uint32_t Length) {
	uint32_t ReadData = 0;
	uint8_t dato = 0;
	/* Loop until data received */
	while (Length--) {
		//uint32_t tickStart = HAL_GetTick();
		tickWrite(0);	   //setup tick timer to Zero
		do {

			/* If it gets a byte from UART_232 It keeps it in dato var. */
			if (HAL_uart_f_ReadByte(UART_232, &dato)) {
				/* Write the byte in the consola */
				HAL_uart_f_WriteByte(UART_USB, dato);
				WiFiRxBuffer.head = dato;

				if (WiFiRxBuffer.head != WiFiRxBuffer.tail) {
					/* serial data available, so return data to user */
					*Buffer++ = WiFiRxBuffer.head;//WiFiRxBuffer.data[WiFiRxBuffer.head++];
					ReadData++;

					/* check for ring buffer wrap */
					if (WiFiRxBuffer.head >= RING_BUFFER_SIZE) {
						/* Ring buffer wrap, so reset head pointer to start of buffer */
						WiFiRxBuffer.head = 0;
					}
					break;
				}
			}
		} while ((tickRead()) < DEFAULT_TIME_OUT);
	}

	return ReadData;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
