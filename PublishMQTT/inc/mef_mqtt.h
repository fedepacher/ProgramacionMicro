/*
 * mef_mqtt.h
 *
 *  Created on: Apr 13, 2020
 *      Author: fedepacher
 */

#ifndef FEDE_PUBLISHMQTT_INC_MEF_MQTT_H_
#define FEDE_PUBLISHMQTT_INC_MEF_MQTT_H_

#include "../../PublishMQTT/inc/esp8266.h"

/*
 * @brief Send connect packet to the broker mqtt.
 */
ESP8266_StatusTypeDef mqtt_Connect(void);

/*
 * @brief Send publish packet to the broker mqtt.
 */
ESP8266_StatusTypeDef mqtt_Publisher(void);

#endif /* FEDE_PUBLISHMQTT_INC_MEF_MQTT_H_ */
