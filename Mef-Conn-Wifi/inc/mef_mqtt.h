/*
 * mef_mqtt.h
 *
 *  Created on: Apr 13, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_MEF_CONN_WIFI_INC_MEF_MQTT_H_
#define FEDE_MEF_CONN_WIFI_INC_MEF_MQTT_H_

#include "esp8266.h"

/*
 * @brief Send connect packet to the broker mqtt.
 */
ESP8266_StatusTypeDef mqtt_Connect(void);

/*
 * @brief Send publish packet to the broker mqtt.
 */
ESP8266_StatusTypeDef mqtt_Publisher(void);

#endif /* FEDE_MEF_CONN_WIFI_INC_MEF_MQTT_H_ */
