/*
 * esp8266_mef.h
 *
 *  Created on: Apr 10, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_PUBLISHMQTT_INC_ESP8266_MEF_H_
#define FEDE_PUBLISHMQTT_INC_ESP8266_MEF_H_

#include "../../PublishMQTT/inc/esp8266.h"


typedef enum{
		INIT,			//	corresponde al envio de at->ok, at+cwmode=1 -> ok, at+cipmux=0 -> ok
		JOINACCESSPOINT,	//	coresponde al envio de AT+CWJAP=\"Ssid\",\"Password\"%c%c"
		GETIPADDRESS,
		ESTABLISHCONNECTION,
		CONNECT_BROKER,
		PUBLISH_BROKER,
		CLOSECONNECTION,
		RECEIVEDATA,
		QUITACCESSPOINT,
		DESCONECT_WIFI,
		RESTART,
		DEINIT,
		STANDBY,
}esp_state;

/**
 * @brief  setup broker connection.
 * @param  connection_info: connection information.
 */
void esp8266_broker_setup(ESP8266_ConnectionInfoTypeDef* connection_info);

/**
 * @brief  FSM to connect to wifi network an to the broker
 * @param  connection_info: connection information.
 * @param  state:			stato for the FSM
 * @retval ESP8266_StatusTypeDef: if the connection was ok or not.
 */
ESP8266_StatusTypeDef esp8266_mef_running(ESP8266_ConnectionInfoTypeDef* connection_info, esp_state* state);

#endif /* FEDE_PUBLISHMQTT_INC_ESP8266_MEF_H_ */
