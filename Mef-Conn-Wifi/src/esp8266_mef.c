/*
 * esp8266_mef.c
 *
 *  Created on: Apr 10, 2020
 *      Author: fedepacher
 */
#include "esp8266_mef.h"
#include "wifi_credentials.h"
#include "mef_mqtt.h"

static uint8_t IpAddress;


void esp8266_broker_setup(ESP8266_ConnectionInfoTypeDef* connection_info) {
	connection_info->connectionType = ESP8266_TCP_CONNECTION;
	connection_info->ipAddress = "broker.hivemq.com";
	connection_info->port = 1883;
	connection_info->isServer = ESP8266_FALSE;


}

ESP8266_StatusTypeDef esp8266_mef_running(ESP8266_ConnectionInfoTypeDef* connection_info, esp_state* state) {

	ESP8266_StatusTypeDef Status;

	switch (*state) {
	case INIT:
		Status = ESP8266_Init();
		*state = JOINACCESSPOINT;
		break;
	case JOINACCESSPOINT:
		Status = ESP8266_JoinAccessPoint(WIFI_AP_SSID, WIFI_AP_PASS);
		*state = GETIPADDRESS;
		break;
	case GETIPADDRESS:
  		Status = ESP8266_GetIPAddress(ESP8266_STATION_MODE, &IpAddress);
  		*state = ESTABLISHCONNECTION;
		break;
	case ESTABLISHCONNECTION:
		Status = ESP8266_EstablishConnection(connection_info);
		*state = CONNECT_BROKER;
 		break;
	case CONNECT_BROKER:
 		Status = mqtt_Connect();
 		*state = PUBLISH_BROKER ;
		break;
	case PUBLISH_BROKER:
	 	Status = mqtt_Publisher();
		break;
	case CLOSECONNECTION:
        Status = ESP8266_CloseConnection(0);
        *state = STANDBY;
		break;

	/*case RESTART:
		Status = ESP8266_OK;
	    //    Status = ESP8266_Restart();
		break;*/

	case STANDBY:
			Status = ESP8266_OK;
		    //    Status = ESP8266_Restart();
	break;

	default:
		Status = ESP8266_OK;
		break;
	}
  	return Status;
}

