/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones
#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "semaforo.h"

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

	semaphore_t sem1;

		//FIXME: chequear valor devuelto por la funcion

		if(!semaphoreInit(&sem1)){
			//prender led rgb indicando falla
			gpioWrite(LEDR, ON);
			gpioWrite(LEDG, OFF);
			while(TRUE);	// si falla cuelgo el sistema
		}
		else{
			gpioWrite(LEDR, OFF);
			gpioWrite(LEDG, ON);
		}


	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {

		semaphore_control(&sem1);

	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}

/**	@brief Funcion que prende los leds segun parametro de ingreso
 * 	@param[in]	led	Referencia al led a prender *
 */

