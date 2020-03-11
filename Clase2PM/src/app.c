/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "../../Clase2PM/inc/app.h"         // <= Su propia cabecera

#include "../../Clase2PM/inc/board_ext.h"
#include "../../Clase2PM/inc/key.h"
#include "sapi.h"        // <= Biblioteca sAPI


#define DUTY_CICLE 200

/*=====[Encabezados de funciones]=============================================*/



/*=====[Typedef]==============================================================*/\
typedef enum{
	PARADA = 0,
	ADELANTE,
	ATRAS,
	TOTAL_ESTADOS
}estado_secuencia;

typedef enum{
	APAGAR,
	PRENDER
}estado_led;


const uint8_t cantidad_leds = 3;	//indica la cantidad de led disponibles

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   key_init();		//inicializacion del arreglo contenedor de los pulsadores a FALSE, es decir, no pulsados


   // ---------- REPETIR POR SIEMPRE --------------------------


   while( TRUE ) {


	   key_periodicTask1ms();		//chequeo por pooling si un pulsador fue presionado

	   if(key_getPressEv(BOARD_SW_ID_1)){	//si se pulsa el sw1 comienza secuencia para un lado
		   board_setLed(BOARD_LED_ID_1, BOARD_LED_MSG_TOGGLE);
	   }


	   delay(1);

   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/**	@brief Funcion que prende los leds segun parametro de ingreso
 * 	@param[in]	led	Referencia al led a prender *
 */



