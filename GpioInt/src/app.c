/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "chip.h"       // <= Biblioteca LPCOpen, capa chip (del fabricante NXP)

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

// Handler interrupt from GPIO pin or GPIO pin mapped to PININT
void PININT_IRQ_HANDLER(void) {
	// Se da aviso que se trato la interrupcion
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(PININT_INDEX));

	// Se realiza alguna accion.
	gpioToggle(LEDB);
}

/*=====[Encabezados de funciones]=============================================*/

/*=====[Typedef]==============================================================*/\


// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
      int main(void) {
	// ---------- CONFIGURACIONES ------------------------------

	// Inicializar y configurar la plataforma
	boardConfig();

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

	// ---> Fin de funciones LPCOpen

	// ---------- REPETIR POR SIEMPRE --------------------------

	while ( TRUE) {

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}

/**	@brief Funcion que prende los leds segun parametro de ingreso
 * 	@param[in]	led	Referencia al led a prender *
 */

