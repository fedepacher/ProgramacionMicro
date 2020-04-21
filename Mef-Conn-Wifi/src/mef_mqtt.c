/*
 * mef_mqtt.c
 *
 *  Created on: Apr 13, 2020
 *      Author: fedepacher
 */

// Include
#include "MQTTPacket.h"
#include "transport.h"
#include "networkwrapper.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sapi.h"
#include "mef_mqtt.h"
#include "led.h"
#include "key_generic.h"

#define CONNECTION_KEEPALIVE_S 60UL
#define TRIAL_CONNECTION_TIME	5

delay_t wakeTime;
static unsigned char buffer[128];
int32_t transport_socket;


ESP8266_StatusTypeDef mqtt_Connect(void) {

	MQTTTransport transporter;
	int32_t result;
	int32_t length;

	ESP8266_StatusTypeDef Status = ESP8266_OK;

	// Transport layer uses the esp8266 networkwrapper.
	static transport_iofunctions_t iof = { network_send, network_recv };
	transport_socket = transport_open(&iof);

	// Turn the LED off.
	turnOff(LED3);

	// Initialize the adc.
	adcConfig(ADC_ENABLE); /* ADC */

	int32_t internalState = 0;

	while(internalState < TRIAL_CONNECTION_TIME)
	{
		// Populate the transporter.
		transporter.sck = &transport_socket;
		transporter.getfn = transport_getdatanb;
		transporter.state = 0;

		// Populate the connect struct.
		MQTTPacket_connectData connectData =
		MQTTPacket_connectData_initializer;
		connectData.MQTTVersion = 4; //3;
		connectData.clientID.cstring = "fede";
		connectData.keepAliveInterval = CONNECTION_KEEPALIVE_S * 2;
		length = MQTTSerialize_connect(buffer, sizeof(buffer), &connectData);

		// Send CONNECT to the mqtt broker.
		if ((result = transport_sendPacketBuffer(transport_socket, buffer,
				length)) == length) {
			Status = ESP8266_OK;
			break;
		} else {
			Status = ESP8266_ERROR;
			internalState++;
		}
	}

	return Status;
}


ESP8266_StatusTypeDef mqtt_Publisher(void) {

	MQTTTransport transporter;
	int32_t result;
	int32_t length;

	ESP8266_StatusTypeDef Status = ESP8266_OK;

	// Transport layer uses the esp8266 networkwrapper.
	static transport_iofunctions_t iof = { network_send, network_recv };
	transport_socket = transport_open(&iof);

	// Turn the LED on.
	turnOn(LED3);
	tickWrite(0); //set tick timer to zero

	// Populate the publish message.
	MQTTString topicString = MQTTString_initializer;
	topicString.cstring = "test/pdm";
	unsigned char payload[16];
	length = MQTTSerialize_publish(buffer, sizeof(buffer), 0, 0, 0, 0,
			topicString, payload,
			(length = sprintf(payload, "%d", (int) adcRead(CH2))));

	// Send PUBLISH to the mqtt broker.
	if ((result = transport_sendPacketBuffer(transport_socket, buffer, length))
			== length) {
		Status = ESP8266_OK;
		// Wait 5s.
		while (tickRead() < 500) {
		}

	} else {
		// Start over.
		Status = ESP8266_ERROR;
	}
	// Turn the LED off.
	turnOff(LED3);
	return Status;
}

