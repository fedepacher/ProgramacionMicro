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
#include "HAL_uart_f.h"

/*=====[Macros de definicion de constantes privadas]=========================*/
#define BAUD_RATE 115200 // Baudrate por defecto del ESP8266

// SCU
#define GPIO0_SCU_PORT   6
#define GPIO0_SCU_PIN    1
#define GPIO0_SCU_FUNC   SCU_MODE_FUNC0

// GPIO							//{ {PinNamePortN ,PinNamePinN}, PinFUNC, {GpioPortN, GpioPinN} }
#define GPIO0_GPIO_PORT  0		//sale de sapi_gpio.c { {1, 0}, FUNC0, {0, 9} },   // 36   TEC3    TEC_3
#define GPIO0_GPIO_PIN   9		//sale de sapi_gpio.c { {1, 0}, FUNC0, {0, 9} },   // 36   TEC3    TEC_3

// Interrupt
#define PININT_INDEX         0                  // PININT index used for GPIO mapping
#define PININT_IRQ_HANDLER   GPIO0_IRQHandler   // GPIO interrupt IRQ function name
#define PININT_NVIC_NAME     PIN_INT0_IRQn      // GPIO interrupt NVIC interrupt name

/*=====[Macros estilo funcion privadas]======================================*/
typedef enum {
	MODO_AT, MODO_WIFI,
} esp_mode;
/*=====[Definiciones de tipos de datos privados]=============================*/

esp_mode mode_esp;
esp_state state_esp;
const char str_modo_comando[] = "Modo comando\r\n";
const char str_modo_conexion[] = "Modo MEF conexion broker\r\n";
const char str_boton_pulsado[] = "TEC1 -> Boton pulsado\r\n";
const char str_boton_liberado[] = "TEC1 -> Boton liberado\r\n";
const char str_falla[] = "Falla en conexion\r\n";

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
// Handler interrupt from GPIO pin or GPIO pin mapped to PININT
void PININT_IRQ_HANDLER(void) {
	// Se da aviso que se trato la interrupcion
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));

	// Se realiza alguna accion.
	if(mode_esp == MODO_WIFI){
		state_esp = CLOSECONNECTION;
		gpioToggle(LEDB);
	}


}

/*=====[Implementaciones de funciones privadas]==============================*/
static void resetLEDS(void) {
	turnOff(LEDR);
	turnOff(LEDG);
	turnOff(LEDB);
	turnOff(LED1);
	turnOff(LED2);
	turnOff(LED3);
}

static void modo_reporte_modo_func(bool_t flag_act, bool_t* flag_ant) {
	if (flag_act != *flag_ant) {
		if (flag_act)
			HAL_uart_f_WriteString(UART_USB, str_modo_comando);
		else
			HAL_uart_f_WriteString(UART_USB, str_modo_conexion);
		*flag_ant = flag_act;
	}

}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
  int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();

	//***********************************************************************************
	/* Configuracion de GPIO0 de la EDU-CIAA-NXP como entrada con pull-up */
	gpioConfig(GPIO0, GPIO_INPUT_PULLUP);

	// ---> Comienzo de funciones LPCOpen para configurar la interrupcion

	// Configure interrupt channel for the GPIO pin in SysCon block
	Chip_SCU_GPIOIntPinSel( PININT_INDEX, GPIO0_GPIO_PORT, GPIO0_GPIO_PIN);

	// Configure channel interrupt as edge sensitive and falling edge interrupt
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));
	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));

	// Enable interrupt in the NVIC
	NVIC_ClearPendingIRQ( PININT_NVIC_NAME);
	NVIC_EnableIRQ( PININT_NVIC_NAME);
	//***********************************************************************************

	button_ptr but1;
	button_ptr but2;

	delay_t delay_led;
	ESP8266_StatusTypeDef Status;
	uint8_t dato = 0;
	ESP8266_ConnectionInfoTypeDef connection_info;
	//esp_state esp_state;

	bool_t estado_btn_presianado_ant;
	bool_t estado_btn_liberado_ant;
	uint8_t contador_fallas = 0;

	mode_esp = MODO_AT;

	HAL_uart_f_Init(UART_USB, BAUD_RATE);
	HAL_uart_f_Init(UART_232, BAUD_RATE);

	keyInit(&but1, TEC1);
	keyInit(&but2, TEC2);

	estado_btn_presianado_ant = but1.sw_pressed;
	estado_btn_liberado_ant = but1.sw_released;

	delayInit(&delay_led, 500);

	esp8266_broker_setup(&connection_info);

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {

		key_mef_debounce_generic(&but1);
		key_mef_debounce_generic(&but2);

		if (key_released(&but1)) {
			if (mode_esp == MODO_AT) {
				mode_esp = MODO_WIFI;
			} else {
				mode_esp = MODO_AT;
			}
			resetLEDS();
		}

		//show when  button was pressed
		if (but1.sw_pressed != estado_btn_presianado_ant) {
			estado_btn_presianado_ant = but1.sw_pressed;
			HAL_uart_f_WriteString(UART_USB, str_boton_pulsado);
		}
		//show when button was released
		if (but1.sw_released != estado_btn_liberado_ant) {
			estado_btn_liberado_ant = but1.sw_released;
			HAL_uart_f_WriteString(UART_USB, str_boton_liberado);
		}

		//print msg mode
		//modo_reporte_modo_func(flag_modo, &flag_modo_anterior);

		switch (mode_esp) { //AT command mode
		case MODO_AT:
			contador_fallas = 0;
			state_esp = INIT;
			if (key_released(&but2)) {

				resetLEDS();
				delay(250);
				HAL_uart_f_WriteString(UART_USB, "> Test AT: AT\r\n");
				HAL_uart_f_WriteString(UART_232, "AT\r\n");
			}

			/* Si recibe un byte de la UART_USB lo guardarlo en la variable dato. */
			if (HAL_uart_f_ReadByte(UART_USB, &dato)) {
				/* Se reenvía el dato a la UART_232 realizando un puente entre ambas */
				HAL_uart_f_WriteByte(UART_232, dato);
			}

			/* Si recibe un byte de la UART_232 lo guardarlo en la variable dato. */
			if (HAL_uart_f_ReadByte(UART_232, &dato)) {
				/* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
				HAL_uart_f_WriteByte(UART_USB, dato);
			}

			if (delayRead(&delay_led)) {
				blink(LED1);
			}
			break;
		case MODO_WIFI: //Init esp module

			Status = esp8266_mef_running(&connection_info, &state_esp);
			if (Status != ESP8266_OK) {
				resetLEDS();
				turnOn(LEDR);
				contador_fallas++;
			} else {
				resetLEDS();
				turnOn(LEDG);
			}

			if (contador_fallas >= 3) {
				HAL_uart_f_WriteString(UART_USB, str_falla);
				//esp_state = RESTART;
				contador_fallas = 0;
			}

			if (delayRead(&delay_led)) {
				blink(LED2);
			}
			break;
		default:

			break;
		}

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}

