/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI

#define DUTY_CICLE 500

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
   uint16_t duty_cicle = 0;		//variable que almacena el tiempo apagado/perndido de los leds
   bool_t estado_led = FALSE;	//variable que indica el estado del led TRUE = prender, FALSE = apagar
   uint8_t led_activo = 0;
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {

	   duty_cicle++;

	   if(duty_cicle >= DUTY_CICLE){
		   duty_cicle = 0;
		   if (estado_led){
			   Prender_Leds(led_activo);
		   }
		   else{
			   Apagar_Leds();
		   }
		   led_activo++;
		   if(led_activo >= cantidad_leds)
			   led_activo = 0;
		   estado_led = !estado_led;
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


