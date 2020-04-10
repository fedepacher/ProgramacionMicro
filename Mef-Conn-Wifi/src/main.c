/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
#include "main.h"         // <= Su propia cabecera

#include "sapi.h"        // <= Biblioteca sAPI
#include "key_generic.h"
#include "led.h"
#include "esp8266.h"
#include "esp8266_mef.h"

/*=====[Macros de definicion de constantes privadas]=========================*/
#define BAUD_RATE 115200 // Baudrate por defecto del ESP8266
/*=====[Macros estilo funcion privadas]======================================*/

/*=====[Definiciones de tipos de datos privados]=============================*/

// Tipo de datos que renombra un tipo basico
// Tipo de datos de puntero a funcion
// Tipo de datos enumerado
// Tipo de datos estructua, union o campo de bits
/*=====[Definiciones de Variables globales publicas externas]================*/

/*=====[Definiciones de Variables globales publicas]=========================*/

/*=====[Definiciones de Variables globales privadas]=========================*/


/*=====[Prototipos de funciones privadas]====================================*/

/*=====[Implementaciones de funciones publicas]==============================*/

/*=====[Implementaciones de funciones de interrupcion publicas]==============*/

/*=====[Implementaciones de funciones privadas]==============================*/
static void resetLEDS(void){
	turnOff(LEDR);
	turnOff(LEDG);
	turnOff(LEDB);
	turnOff(LED1);
	turnOff(LED2);
	turnOff(LED3);
}
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
    int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();

	button_ptr but1;
	button_ptr but2;
	button_ptr but3;
	button_ptr but4;
	delay_t delay_led;
	ESP8266_StatusTypeDef Status;
	bool_t flag_modo = TRUE;
	uint8_t dato  = 0;
	esp_state esp_state = 0;

	uartConfig(UART_USB, BAUD_RATE);
	uartConfig(UART_232, BAUD_RATE);

	keyInit(&but1, TEC1);
	keyInit(&but2, TEC2);
	keyInit(&but3, TEC3);
	keyInit(&but4, TEC4);

	delayInit(&delay_led, 500);

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {

		key_mef_debounce_generic(&but1);
		key_mef_debounce_generic(&but2);
		key_mef_debounce_generic(&but3);
		key_mef_debounce_generic(&but4);

		if (key_released(&but1)) {
			flag_modo = !flag_modo;
			resetLEDS();
		}

		if (flag_modo) {//modo para ver si responde el at

			if (key_released(&but2)) {
				delay(250);
				uartWriteString(UART_USB, "> Test AT: AT\r\n");
				uartWriteString(UART_232, "AT\r\n");
			}

			/* Si recibe un byte de la UART_USB lo guardarlo en la variable dato. */
			if (uartReadByte(UART_USB, &dato)) {
				/* Se reenvía el dato a la UART_232 realizando un puente entre ambas */
				uartWriteByte(UART_232, dato);
			}

			/* Si recibe un byte de la UART_232 lo guardarlo en la variable dato. */
			if (uartReadByte(UART_232, &dato)) {
				/* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
				uartWriteByte(UART_USB, dato);
			}

			if (delayRead(&delay_led)) {
				blink(LED1);
			}
		} else {//modo inicializacion esp
			if (key_released(&but2)) {
				Status = esp8266_mef_running(esp_state);
				if (Status != ESP8266_OK) {
					resetLEDS();
					turnOn(LEDR);
				} else {
					resetLEDS();
					turnOn(LEDG);
				}
				esp_state++;
			}

			if (delayRead(&delay_led)) {
				blink(LED2);
			}
		}
	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}

/**	@brief Funcion que prende los leds segun parametro de ingreso
 * 	@param[in]	led	Referencia al led a prender *
 */

