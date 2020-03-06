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

   uint16_t duty_cicle = 0;		//variable que almacena el tiempo apagado/perndido de los leds
   estado_secuencia sentido = PARADA;		//indica el sentido de giro de los leds; 0 = L3 -> L2 -> L1
   estado_secuencia sentido_anterior = sentido;	//indica el sentido anterior
   int8_t led_encender = 0;		//indica que led tiene que encender en la secuencia, le puse int8_t porque cuando invierte sentido llega a un valor negativo

   estado_led estado = PRENDER;		//indica si debe proceder con el avance al proximo led

   // ---------- REPETIR POR SIEMPRE --------------------------


   while( TRUE ) {

	   duty_cicle++;
	   key_periodicTask1ms();		//chequeo por pooling si un pulsador fue presionado

	   if(key_getPressEv(BOARD_SW_ID_1)){	//si se pulsa el sw1 comienza secuencia para un lado
		   sentido++;
		   if(sentido >= TOTAL_ESTADOS)
			   sentido = PARADA;
	   }

	   switch(sentido)
	   {
	   case PARADA:		//limpia todos los leds
		   duty_cicle = 0;
		   if(sentido != sentido_anterior){
			   sentido_anterior = sentido;
			   int i = 0;
		   	   for( i = 0; i <= BOARD_LED_ID_TOTAL; i++){
			   	   board_setLed(i, BOARD_LED_MSG_OFF);
		   	   }
		   }
		   break;
	   case	ADELANTE:	//sentido hacia adelante
		   sentido_anterior = sentido;
		   if(duty_cicle >= DUTY_CICLE){
			   duty_cicle = 0;

			   switch(estado){
			   case	APAGAR:
				   board_setLed(led_encender, BOARD_LED_MSG_OFF);
				   led_encender++;
				   if(led_encender >= BOARD_LED_ID_TOTAL){
					   led_encender = BOARD_LED_ID_1;
				   }
				   estado = PRENDER;
				   break;
			   case PRENDER:
				   board_setLed(led_encender, BOARD_LED_MSG_ON);
				   estado = APAGAR;
				   break;
			   default:
				   break;

			   }
		   }

		   break;

	   case ATRAS:		//sentido hacia atras
		   sentido_anterior = sentido;
		   if(duty_cicle >= DUTY_CICLE){
			   duty_cicle = 0;

			   switch(estado){
			   case	APAGAR:
				   board_setLed(led_encender, BOARD_LED_MSG_OFF);
				   led_encender--;
				   if(led_encender < BOARD_LED_ID_1){
					   led_encender = BOARD_LED_ID_TOTAL - 1;
				   }
				   estado = PRENDER;
				   break;
			   case PRENDER:
				   board_setLed(led_encender, BOARD_LED_MSG_ON);
				   estado = APAGAR;
				   break;
			   default:
				   break;

			   }
		   }
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



