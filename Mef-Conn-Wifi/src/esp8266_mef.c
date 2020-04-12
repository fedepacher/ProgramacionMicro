/*
 * esp8266_mef.c
 *
 *  Created on: Apr 10, 2020
 *      Author: fedepacher
 */
#include "esp8266_mef.h"
#include "wifi_credentials.h"

static uint8_t IpAddress;

void esp8266_broker_setup(ESP8266_ConnectionInfoTypeDef* connection_info) {
	connection_info->connectionType = ESP8266_TCP_CONNECTION;
	connection_info->ipAddress = "broker.hivemq.com";
	connection_info->port = 1883;
	connection_info->isServer = ESP8266_FALSE;

}

ESP8266_StatusTypeDef esp8266_mef_running(ESP8266_ConnectionInfoTypeDef* connection_info, esp_state state) {

	ESP8266_StatusTypeDef Status;

	switch (state) {
	case INIT:
		Status = ESP8266_Init();
		break;
	case JOINACCESSPOINT:
		Status = ESP8266_JoinAccessPoint(WIFI_AP_SSID, WIFI_AP_PASS);
		break;
	case GETIPADDRESS:
  		Status = ESP8266_GetIPAddress(ESP8266_STATION_MODE, &IpAddress);//VER ESTO
		break;
	case ESTABLISHCONNECTION:
		Status = ESP8266_EstablishConnection(connection_info);
 		break;
	case SENDDATA:

		break;
	case CLOSECONNECTION:
		Status = ESP8266_CloseConnection(0);
		break;

	default:
		break;
	}
  	return Status;
}

