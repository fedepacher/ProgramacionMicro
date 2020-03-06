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


#define DUTY_CICLE 200

/*=====[Encabezados de funciones]=============================================*/
void Prender_Leds(uint8_t led);
void Apagar_Leds();


/*=====[Typedef]==============================================================*/\



const uint8_t cantidad_leds = 3;	//indica la cantidad de led disponibles

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   key_init();		//inicializacion del arreglo contenedor de los pulsadores a FALSE, es decir, no pulsados

   /*uint16_t duty_cicle = 0;		//variable que almacena el tiempo apagado/perndido de los leds
   bool_t estado_led = FALSE;	//variable que indica el estado del led TRUE = prender, FALSE = apagar
   int8_t led_activo = 0;
   bool_t sentido_giro = 1;		//indica el sentido de giro de los leds; 0 = L3 -> L2 -> L1
   */
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {

	   key_periodicTask1ms();		//chequeo por pooling si un pulsador fue presionado

	   if(key_getPressEv(BOARD_SW_ID_1))
		   board_setLed(BOARD_LED_ID_1, BOARD_LED_MSG_TOGGLE);


	   if(key_getPressEv(BOARD_SW_ID_2))
	  		   board_setLed(BOARD_LED_ID_2, BOARD_LED_MSG_TOGGLE);

	   if(key_getPressEv(BOARD_SW_ID_3))
	  	  		   board_setLed(BOARD_LED_ID_3, BOARD_LED_MSG_TOGGLE);

	   /*duty_cicle++;

	   if(duty_cicle >= DUTY_CICLE){
		   duty_cicle = 0;
		   if (estado_led){
			   Prender_Leds(led_activo);
			   if(sentido_giro == 0){
				   led_activo++;
			   }
			   else{
				   led_activo--;
			   }
		   }
		   else{
			   Apagar_Leds();
		   }

		   if(led_activo >= cantidad_leds){
			   led_activo = 0;
		   }
		   else{
			   if(led_activo <0)
				   led_activo = cantidad_leds;
		   }

		   estado_led = !estado_led;
	   }*/

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

void Prender_Leds(uint8_t led)
{
	switch(led){
	case 0:
		gpioToggle(LED1);
		break;
	case 1:
		gpioToggle(LED2);
		break;
	case 2:
		gpioToggle(LED3);
		break;
	}

}

/**	@brief	Funcion que produce el apagado de todos los leds *
 */
void Apagar_Leds(){
	gpioWrite( LED1, OFF );
	gpioWrite( LED2, OFF );
	gpioWrite( LED3, OFF );
}


