/*
 * esp8266_mef.h
 *
 *  Created on: Apr 10, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_MEF_CONN_WIFI_INC_ESP8266_MEF_H_
#define FEDE_MEF_CONN_WIFI_INC_ESP8266_MEF_H_

#include "esp8266.h"


typedef enum{
		INIT,			//	corresponde al envio de at->ok, at+cwmode=1 -> ok, at+cipmux=0 -> ok
		JOINACCESSPOINT,	//	coresponde al envio de AT+CWJAP=\"Ssid\",\"Password\"%c%c"
		GETIPADDRESS,
		ESTABLISHCONNECTION,
		SENDDATA,
		CLOSECONNECTION,
		RECEIVEDATA,
		QUITACCESSPOINT,
		DESCONECT_WIFI,
		RESTART,
		DEINIT,
}esp_state;

ESP8266_StatusTypeDef esp8266_mef_running(esp_state state);

#endif /* FEDE_MEF_CONN_WIFI_INC_ESP8266_MEF_H_ */
