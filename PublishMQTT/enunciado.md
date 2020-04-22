PdM - Plataforma embebida: EDU-CIAA-NXP

Aplicación:
La aplicación que he desarrollado inicializa el modulo ESP01 basado en ESP8266.
Dicha aplicación simple tiene dos modos de funcionamiento.

Modo 1: 
Al iniciar la edu ciaa entra en el modo que he llamado Modo Comando.
Dicho modo espera a recibir comandos AT por consola. 
Al presionar la tecla TEC2 envía al módulo ESP el comando AT y espera la respuesta OK. 
Este modo es básicamente una copia del ejemplo provisto en el firmware v3 y fue puesto 
en el software dado los problemas que mi ESP01 presenta. El mismo se reinicia constantemente 
y hace cosas que aun no logro entender. Entrando en este modo puedo saber si el módulo 
funciona correctamente.

Modo 2:
Al presionar la tecla TEC1 pasa al modo que he llamado “Modo MEF conexión broker”.
Dicho modo ejecuta una máquina de estado diagramada en la figura 1. En el estado 
INIT (S1), se inicializa el modulo ESP01 en modo estación (cliente) (CWMODE=1) y en modo 
estación única (CIPMUX=0).
En el estado JOINACCESSPOINT(S2) se conecta a una red preexistente cuyo usuario y contraseña 
están almacenadas en variables de tipo constantes.
El estado GETIPADDRESS (S3) obtiene la ip a la cual está conectado en el router.
Luego pasa al estado ESTABLISHCONNECTION (S4) en el cual se conecta a un broker y un puerto 
predeterminado, en este ejemplo el broker es broker.hivemq.com y el puerto por defecto es 1883.
El estado SENDDATA (S5) es un estado que no está implementado por el momento por lo que pasará 
al estado final CLOSECONNECTION (S6) el cual cerrará la conexión con el broker.
Por último se llega al estado STANDBY (S7) en el cual permanecerá hasta que se presione la 
tecla TEC1.
Si cualquiera de los estados devuelve un error este se reflejará en el LEDR y la secuencia 
volverá al estado INIT  a reintentar la conexión, si después de 3 intentos el error continúa se 
mostrará en pantalla el mensaje de error. El pasaje exitoso de estados se refleja con el LEDG 
encendido.
El sistema funcionando en modo 1 mantendrá un led (LED1) parpadeando indicando que dicho modo 
funciona con normalidad. Al cambiar al modo 2 el LED2 es el que procederá a parpadear.

Periféricos (1 ó 2): 
UART, GPIO

