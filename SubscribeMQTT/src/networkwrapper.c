/**
 * @file      networkwrapper.c
 * @author    Atakan S.
 * @date      01/01/2019
 * @version   1.0
 * @brief     Network wrapper for PAHO MQTT project based on ESP8266.
 *
 * @copyright Copyright (c) 2018 Atakan SARIOGLU ~ www.atakansarioglu.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

// Includes.
#include "networkwrapper.h"

#include <string.h>
#include "esp8266.h"

// Variables.
//static char network_host[32] = "iot.eclipse.org";///< HostName i.e. "test.mosquitto.org"
//static unsigned short int network_port = 1883;///< Remote port number.
static unsigned short int network_keepalive = 20;///< Default keepalive time in seconds.
static char network_ssl = ESP8266_FALSE;///< SSL is disabled by default.
static int network_send_state = 0;///< Internal state of send.
static int network_recv_state = 0;///< Internal state of recv.

// Global time provider.
extern long unsigned int network_gettime_ms(void);///< Returns 32bit ms time value.

void network_init(void){ }

void network_close(void){ }

/*int network_connect(const char * host, const unsigned short int port, const unsigned short int keepalive, const char ssl){
	// Get connection info.
	strcpy(network_host, host);
	network_port = port;
	network_keepalive = keepalive;
	network_ssl = ssl;

	// Reset the internal states.
	network_send_state = 0;
	network_recv_state = 0;

	// Success.
	return 0;
}*/

int network_send(uint8_t* Buffer, uint32_t Length){
	ESP8266_StatusTypeDef Status = ESP8266_OK;
		// Send the data.
	Status = ESP8266_SendData(Buffer, Length); //ESP82_Send(address, bytes);


	// In progress .
	if(Status == ESP8266_OK)
		return Length;
	if(Status == ESP8266_ERROR)
		return -1;
	//In progress
	return 0;
}

int network_recv(unsigned char *address, unsigned int maxbytes){
	static char receiveBuffer[128];
	static uint32_t receiveBufferBack = 0;
	static uint32_t receiveBufferFront = 0;
	uint32_t actualLength;
	uint32_t RetLength;

	// State Machine.
	ESP8266_StatusTypeDef Status;
	switch(network_recv_state) {
	case 0:
		Status = ESP8266_ReceiveData(receiveBuffer, sizeof(receiveBuffer), &RetLength);
		if(RetLength > 0 && RetLength < sizeof(receiveBuffer)){
			// Set the buffer pointers.
			receiveBufferBack = RetLength;
			receiveBufferFront = 0;

			// To the next state.
			network_recv_state++;
		}
		break;
	case 1:
		// Extract to the out buffer.
		if(receiveBufferFront < receiveBufferBack) {
			// Get actual length.
			actualLength = (receiveBufferBack - receiveBufferFront);
			if(actualLength > maxbytes){
				actualLength = maxbytes;
			}

			// Extract the actual bytes.
			memcpy(address, &receiveBuffer[receiveBufferFront], actualLength);
			receiveBufferFront += actualLength;

			// Buffer is empty.
			if(receiveBufferBack == receiveBufferFront) {
				network_recv_state = 0;
			}

			// Return the count.
			return actualLength;
		}
		break;
	default:
		// Reset the state machine.
		network_recv_state = 0;
	}

	// Fall-back on error.
	if(Status == ESP8266_ERROR){
		// Reset the state machine.
		network_recv_state = 0;
		
		// Error.
		return -1;
	}

	// In progress.
	return 0;
}
