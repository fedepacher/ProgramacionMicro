PdM - Ejercicios clase 1

Ejercicio 2 [opcional]

Objetivo

Medir el tiempo de pulsación de un botón y mostrar el tiempo medido encendiendo un LED.

Resumen

El programa espera a que un botón sea pulsado. Mientras el botón está pulsado, se mide el tiempo utilizando un contador hasta que el botón es soltado. En ese momento, se enciende el led asociado al botón durante el tiempo calculado.

Comentarios

Para medir el tiempo del botón es posible implementar un bucle iterativo que se extienda mientras el botón está apretado. Dentro de ese bucle, existirá un delay pequeño (por ejemplo, de 1 milisegundo) y por cada iteración se incrementará en 1 el contador. Cuando el bucle finaliza, significa que el botón fue soltado y en el contador tendremos la cantidad de milisegundos que debemos encender el led.

Para pensar

Luego de resolver el problema, analice:
¿Qué sucede si mientras estoy pulsando una tecla, comienzo a pulsar otra?
¿Qué sucede si mientras el LED está encendido mostrando el tiempo de una tecla, presiona otra tecla (o la misma)?
