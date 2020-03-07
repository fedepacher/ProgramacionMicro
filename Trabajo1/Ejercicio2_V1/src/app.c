/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "board_ext.h"
#include "key.h"


#define DUTY_CYCLE	200

/*=====[Encabezados de funciones]=============================================*/
/**	@brief	Funcion que me indica que la placa esta viva
 *
 */
void heartRate(int32_t* tick);


/*=====[Typedef]==============================================================*/\
typedef enum{
	APAGAR = 0,
	PRENDER
}estado_led;




// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   key_init();		//inicializacion del arreglo contenedor de los pulsadores a FALSE, es decir, no pulsados

   int32_t contador = 0;		//cuenta los milisegundos pulsados el boton
   estado_led estado = PRENDER;	//indica el proximo estado del led
   int32_t tick = 0;
   int32_t* p_tick = &tick;
   // ---------- REPETIR POR SIEMPRE --------------------------


   while( TRUE ) {

	   tick++;
	   heartRate(p_tick);

	   key_periodicTask1ms();		//chequeo por pooling si un pulsador fue presionado

	   if(key_getPressEv(BOARD_SW_ID_1)){
		   contador++;
		   estado = APAGAR;
	   }
	   else{
		   estado = PRENDER;
	   }



	   switch(estado){
	   case APAGAR:
		   board_setLed(BOARD_LED_ID_1, BOARD_LED_MSG_OFF);
		   break;

	   case PRENDER:
		   while(contador > 0){
			   board_setLed(BOARD_LED_ID_1, BOARD_LED_MSG_ON);
			   contador--;
			   delay(1);
		   }
		   contador = 0;
		   break;
	   default:

		   break;
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

void heartRate(int32_t* tick){
	if(*tick >= DUTY_CYCLE)
	{
		*tick = 0;
		board_setLed(BOARD_LED_ID_2, BOARD_LED_MSG_TOGGLE);
	}
}

