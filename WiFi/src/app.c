/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
//#include "../../Clase3PM/inc/app.h"         // <= Su propia cabecera

//#include "../../Clase3PM/inc/board_ext.h"
//#include "../../Clase3PM/inc/key.h"

#include "app.h"         // <= Su propia cabecera

#include "sapi.h"        // <= Biblioteca sAPI



/*==================[macros and definitions]=================================*/

#define BAUD_RATE 115200 // Baudrate por defecto del ESP8266

#define		PORT			1883
#define		BROKER			"broker.hivemq.com"
#define		CONNECT_TYPE	"TCP"
#define		CHANNEL			4
#define 	CONNECT			10 2C 00 06 4D 51 49 73 64 70 03 C2 00 3C 00 06 41 42 43 44 45 46 00 08 64 78 78 6B 67 6B 70 70 00 0C 71 41 55 5A 42 64 61 53 49 55 4C 78
#define 	PUBLISH			30 13 00 08 76 61 6C 65 74 72 6F 6E 68 65 6C 6C 6F 72 61 76 69
#define		SUBSCRIBE		82 0D 00 01 00 08 76 61 6C 65 74 72 6F 6E 00


/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

void imprimirMensajeDeBienvenida( void )
{
   /*
   AT+CWMODE?
   AT+CWMODE=3
   */
   // Imprimo el mensaje de bienvenida
   uartWriteString( UART_USB,
      "Bievenido al asistente de configuracion del modulo ESP8266\r\n" );
   uartWriteString( UART_USB,
      "Antes de continuar, por favor asegurese que su terminal\r\n" );
   uartWriteString( UART_USB,
      "serie dispone del terminador CR+LF (enter)\r\n\r\n" );
   uartWriteString( UART_USB,
      "A continuacion se realiza un listado de algunos de los\r\n" );
   uartWriteString( UART_USB, "comandos AT disponibles:\r\n\r\n" );
   uartWriteString( UART_USB,
      "> Saber si el modulo responde correctamente: AT\r\n" );
   uartWriteString( UART_USB,
      "> Version del Firmware: AT+GMR\r\n" );
   uartWriteString( UART_USB, "> Resetear el modulo: AT+RST\r\n" );
   uartWriteString( UART_USB,
      "> Listar todas las redes disponibles: AT+CWLAP\r\n" );
   uartWriteString( UART_USB,
      "> Checkear la red actual: AT+CWJAP?\r\n" );
   uartWriteString( UART_USB,
      "> Unirse a una red: AT+CWJAP=\"nombreRedInalambrica\",\"password\"\r\n" );
   uartWriteString( UART_USB,
      "  - NOTA: Las comillas dobles son parte del mensaje\r\n" );
   uartWriteString( UART_USB,
      "> Salir de la red: AT+CWQAP\r\n" );

   delay(100);
}



void connect_ESP8266(void){

	uartWriteString( UART_232,
			"AT+CIPMUX=1\r\n" );
	delay(250);
	uartWriteString( UART_232,
			"AT+CIPSTART=CHANNEL,CONNECT_TYPE,BROKER,PORT\r\n" );
	delay(250);
	uartWriteString( UART_232,
			"AT+CIPSEND=CHANNEL, 100\r\n" );
	delay(250);
	uartWriteString( UART_232,
			"AT+CIPSEND=CONNECT\r\n" );
	delay(250);
	uartWriteString( UART_232,
				"AT+CIPSEND=PUBLISH\r\n" );
	delay(250);
}



/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
       boardConfig();



   /* Inicializar las UART a 115200 baudios (si no funciona probar a 9600) */
   uartConfig( UART_USB, BAUD_RATE );
   uartConfig( UART_232, BAUD_RATE );

   uint8_t dato  = 0;

      imprimirMensajeDeBienvenida();

      /* ------------- REPETIR POR SIEMPRE ------------- */
      while(1) {

         /* Si presionan TEC1 muestro el mensaje de bienvenida */
         if( !gpioRead( TEC1 ) ){
            gpioWrite( LEDB, ON );
            imprimirMensajeDeBienvenida();
            gpioWrite( LEDB, OFF );
         }
         if( !gpioRead( TEC2 ) ){
            delay(250);
            uartWriteString( UART_USB,
               "> Test AT: AT\r\n" );
            uartWriteString( UART_232,
               "AT\r\n" );
         }
         if( !gpioRead( TEC3 ) ){
        	 delay(250);
        	connect_ESP8266();
         }

         /* Si recibe un byte de la UART_USB lo guardarlo en la variable dato. */
         if( uartReadByte( UART_USB, &dato ) ){
            /* Se reenvía el dato a la UART_232 realizando un puente entre ambas */
            uartWriteByte( UART_232, dato );
         }

         /* Si recibe un byte de la UART_232 lo guardarlo en la variable dato. */
         if( uartReadByte( UART_232, &dato ) ){
            /* Se reenvía el dato a la UART_USB realizando un puente entre ambas */
            uartWriteByte( UART_USB, dato );
         }

      }

      /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
         por ningun S.O. */
      return 0 ;
}

/*==================[end of file]============================================*/
