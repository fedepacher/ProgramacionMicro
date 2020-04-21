/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "key_generic.h"
#include "led.h"
#include "sapi_uart.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*=====[Macros de definicion de constantes privadas]=========================*/

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

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
 int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();
	uartInit(UART_USB, 115200);

	char buffer[128] = "HOLA MAN c0mo es \0as, \0\0bien";
	char text[128];
	int i;
	int32_t lenght;
	int32_t total_lenght;
	button_ptr but1;
	delay_t titilarLed1;

	delayInit(&titilarLed1, 500);
	keyInit(&but1, TEC1);

	lenght = strlen((char *) buffer);
	total_lenght = sizeof(buffer);

	memset(text, '\0', sizeof(text));
	sprintf((char *) text, "strlen: %d%c%c", lenght, '\r', '\n');
	uartWriteString(UART_USB, text);
	memset(text, '\0', sizeof(text));
	sprintf((char *) text, "sizeof: %d%c%c", total_lenght, '\r', '\n');
	uartWriteString(UART_USB, text);

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {
		key_mef_debounce_generic(&but1);

		if (but1.sw_released) {
			uint32_t i = 0;
			char caracter;

			for (i = 0; i < 28; i++) {
				if (buffer[i] == '\0')
					caracter = 0;
				else
					caracter = buffer[i];
				uartWriteByte(UART_USB, caracter);
			}
		}
		if (delayRead(&titilarLed1)) {
			blink(LEDB);
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

