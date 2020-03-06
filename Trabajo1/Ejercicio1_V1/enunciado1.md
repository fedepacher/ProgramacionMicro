PdM - Ejercicios clase 1

Ejercicio 1 

Objetivo
Practicar la utilización del lenguaje C y el desarrollo de programas en microcontroladores. En particular utilizar las funciones de manejo de GPIO y retardos bloqueantes (Delays).

Resumen
Implementar un programa que controle el sentido en que se encienden consecutivamente los LEDs de la EDU-CIAA-NXP, mediante un pulsadores.
Condiciones de funcionamiento
- Utilizar solamente los leds LED1, LED2 y LED3.
- Inicialmente, la secuencia es: LED1 -> LED2 -> LED3 -> LED1 ...
- El período de encendido de cada led debe ser 1 seg con duty 50%.
- Una vez que se pasa al siguiente led los demás deberán apagarse.
- Controlar el sentido de la secuencia con la tecla TEC1.  Cada vez que se presione la TEC1 se debe invertir el sentido de la secuencia. Las secuencias posibles son dos:
LED1 -> LED2 -> LED3 -> LED1 ...
LED1 -> LED3 -> LED2 -> LED1 ...


Para pensar al finalizar el ejercicio:

1-¿Cuán sencillo es agregar un nuevo led a la secuencia, supongamos el LEDB?
2-¿Se puede cambiar el sentido de la secuencia en cualquier momento de la ejecución  o se debe esperar algún momento en especial? ¿Cuál? ¿Por qué?
3-¿Responde adecuadamente el programa a la pulsación de la tecla? 
4-¿Qué pasa si el tiempo de cada led aumenta o disminuye? ¿Cómo responde la tecla, mejor o peor?

