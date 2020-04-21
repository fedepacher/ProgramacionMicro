/*
 * esp8266.c
 *
 *  Created on: Apr 10, 2020
 *      Author: fedepacher
 */

#ifndef __ESP8266_H
#define __ESP8266_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Private define ------------------------------------------------------------*/
#define MAX_BUFFER_SIZE         1500
#define MAX_AT_CMD_SIZE         256
#define AT_OK_STRING            "OK\r\n"
#define AT_IPD_OK_STRING        "OK\r\n\r\n"
#define AT_SEND_OK_STRING       "SEND OK\r\n"
#define AT_SEND_PROMPT_STRING   "OK\r\n>"
#define AT_ERROR_STRING         "ERROR\r\n"
#define AT_IPD_STRING           "+IPD,"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  ESP8266_FALSE         = 0,
  ESP8266_TRUE          = 1
} ESP8266_Boolean;

typedef enum
{ 
  ESP8266_OK                            = 0,
  ESP8266_ERROR                         = 1,
  ESP8266_BUSY                          = 2,
  ESP8266_ALREADY_CONNECTED             = 3,
  ESP8266_CONNECTION_CLOSED             = 4,
  ESP8266_TIMEOUT                       = 5,
  ESP8266_IO_ERROR                      = 6,
} ESP8266_StatusTypeDef;

typedef enum
{
  ESP8266_ENCRYPTION_OPEN         = 0,
  ESP8266_ENCRYPTION_WEP          = 1,
  ESP8266_ENCRYPTION_WPA_PSK      = 2,
  ESP8266_ENCRYPTION_WPA2_PSK     = 3,
  ESP8266_ENCRYPTION_WPA_WPA2_PSK = 4,
} ESP8266_EncryptionTypeDef;

typedef enum
{
  ESP8266_STATION_MODE      = 0,
  ESP8266_ACCESSPPOINT_MODE = 1,
  ESP8266_MIXED_MODE        = 2,
} ESP8266_ModeTypeDef;

typedef enum
{
  NORMAL_MODE      = 0,
  UNVARNISHED_MODE = 1
} ESP8266_TransferModeTypeDef;

typedef enum
{
  ESP8266_GOT_IP_STATUS       = 1,
  ESP8266_CONNECTED_STATUS    = 2,
  ESP8266_DISCONNECTED_STATUS = 3,
} ESP8266_ConnectionStatusTypeDef;

typedef enum
{
  ESP8266_TCP_CONNECTION = 0,
  ESP8266_UDP_CONNECTION = 1,
} ESP8266_ConnectionModeTypeDef;

typedef enum
{
  UDP_PEER_NO_CHANGE   = 0,
  UPD_PEER_CHANGE_ONCE = 1,
  UDP_PEER_CHANGE_ALLOWED = 2,
  UDP_PEER_CHANGE_INVALID = -1,
} ESP8266_ConnectionPolicyTypeDef;

typedef struct
{
  ESP8266_ConnectionStatusTypeDef  connectionStatus;
  ESP8266_ConnectionModeTypeDef    connectionType;
  ESP8266_ConnectionPolicyTypeDef  connectionMode;  /* For UDP connections only */
  uint8_t                          connectionID;
  uint8_t*     	                   ipAddress;
  uint32_t                         port;
  uint32_t                         localPort;       /* for UDP connection only */
  ESP8266_Boolean                  isServer;  
} ESP8266_ConnectionInfoTypeDef;

typedef struct
{
  uint8_t*                   ssid;
  uint8_t*                   password;
  uint16_t                   channedID;
  ESP8266_EncryptionTypeDef  encryptionMode;
} ESP8266_APConfigTypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
 * @brief   Initialize the esp8266 module.
 *          IT intitalize the IO to communicate between the MCU and the module, then
 *          test that the modules is working using some basic AT commands.
 *          in case of success the string "OK" is returned inside otherwise
 *	         it is an error.
 * @param   None
 * @retval  ESP8266_OK on sucess, ESP8266_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_Init(void);

/**
 * @brief   Deinitialize the ESP8266 module.
 * @details Restarts the module  and stop the IO. AT command can't be executed
 unless the module is reinitialized.
 * @param   None
 * @retval  ESP8266_OK on sucess, ESP8266_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_DeInit(void);

/**
 * @brief  Restarts the esp8266 module.
 * @param  None
 * @retval ESP8266_OK on sucess, ESP8266_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_Restart(void);

/**
 * @brief  Quit an Access point if any.
 * @param  None
 * @retval returns ESP8266_AT_COMMAND_OK on success and ESP8266_AT_COMMAND_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_QuitAccessPoint(void);

/**
 * @brief  Join an Access point.
 * @param  Ssid: the access point id.
 * @param  Password the Access point password.
 * @retval Returns ESP8266_AT_COMMAND_OK on success and ESP8266_AT_COMMAND_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_JoinAccessPoint(uint8_t* ssid, uint8_t* password);

/**
 * @brief  Get the IP address for the esp8266 in Station mode.
 * @param  Mode: a ESP8266_ModeTypeDef to choose the Station or AccessPoint mode.
 only the Station Mode is supported.
 * @param  IpAddress buffer to contain the IP address.
 * @retval Returns ESP8266_OK on success and ESP8266_ERROR otherwise
 */
ESP8266_StatusTypeDef ESP8266_GetIPAddress(ESP8266_ModeTypeDef mode, uint8_t* ip_address);

/**
 * @brief  Establish a network connection.
 * @param  Connection_info a pointer to a ESP8266_ConnectionInfoTypeDef struct containing the connection info.
 * @retval Returns ESP8266_AT_COMMAND_OK on success and ESP8266_AT_COMMAND_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_EstablishConnection(const ESP8266_ConnectionInfoTypeDef* connection_info);

/**
 * @brief   Close a network connection.
 * @details Use the ALL_CONNECTION_ID to close all connections.
 * @param   Channel_id the channel ID of the connection to close.
 * @retval  Returns ESP8266_AT_COMMAND_OK on success and ESP8266_AT_COMMAND_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_CloseConnection(const uint8_t channel_id);

/**
 * @brief  Send data over the wifi connection.
 * @param  Buffer: the buffer to send
 * @param  Length: the Buffer's data size.
 * @retval Returns ESP8266_OK on success and ESP8266_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_SendData(uint8_t* pData, uint32_t Length);

/**
 * @brief  receive data over the wifi connection.
 * @param  pData the buffer to fill will the received data.
 * @param  Length the maximum data size to receive.
 * @param RetLength the actual data received.
 * @retval returns ESP8266_OK on success and ESP8266_ERROR otherwise.
 */
ESP8266_StatusTypeDef ESP8266_ReceiveData(uint8_t* pData, uint32_t Length, uint32_t* retLength);

#ifdef __cplusplus
}
#endif

#endif /* __ESP8266_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
