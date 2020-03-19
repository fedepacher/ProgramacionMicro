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
#include "semaforo.h"
#include "sapi.h"        // <= Biblioteca sAPI



/*=====[Encabezados de funciones]=============================================*/

/*=====[Typedef]==============================================================*/\


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

		//chequear teclas
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

