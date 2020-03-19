PdM - Ejercicios clase 3
Ejercicio 1 
Objetivo
Modularizar en funciones, archivos y capas un proyecto de controlador de semáforo.
Resumen
Implementar un programa que controle la lógica de funcionamiento de un semáforo implementado con los LEDs de la EDU-CIAA-NXP.
Condiciones de funcionamiento
Módulos:
main.c, main.h
semaforo.c, semaforo.h
led.c, led.h

Dependencias externas:
sAPI.h

El semáforo debe tener los siguientes modos de operación:
Normal: secuencia de luces rojo 3 s, amarillo 500 mS, verde 1s.
Desconectado: amarillo intermitente cada 500 mS.
Alarma: rojo y amarillo intermitente cada 1 s

Con la tecla 1 de la EDU-CIAA-NXP se debe cambiar el modo de operación del semáforo a normal.

Con la tecla 2 de la EDU-CIAA-NXP se debe cambiar el modo de operación del semáforo a desconectado.

Con la tecla 3 de la EDU-CIAA-NXP se debe cambiar el modo de operación del semáforo a alarma.

