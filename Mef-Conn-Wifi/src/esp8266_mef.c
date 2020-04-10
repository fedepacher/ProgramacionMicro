/*
 * esp8266_mef.c
 *
 *  Created on: Apr 10, 2020
 *      Author: fedepacher
 */
#include "esp8266_mef.h"
#include "wifi_credentials.h"


ESP8266_StatusTypeDef esp8266_mef_running(esp_state state){

	ESP8266_StatusTypeDef Status;

	switch(state){
	case INIT:
		Status = ESP8266_Init();
		break;
	case JOINACCESSPOINT:
		Status = ESP8266_JoinAccessPoint(WIFI_AP_SSID, WIFI_AP_PASS);
		break;
	case GETIPADDRESS:

	break;
	case ESTABLISHCONNECTION:

		break;
	case SENDDATA:

		break;
	case CLOSECONNECTION:

		break;


	default:
		break;
	}
	return Status;
}

