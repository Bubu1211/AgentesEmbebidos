#include <Hecho.h>
#include <Regla.h>

Hecho TIERRA_SECA("La tierra esta seca");
Hecho TIERRA_HUM( "La tierra esta húmeda");
Hecho TEMP_ALT 	( "La temperatura es alta");
Hecho TEMP_BAJA	( "La temperatura es baja");
Hecho TEMP_NORMAL ( "La temperatura es normal o adecuada");
Hecho RAD_INT	( "La radiación lumínica es intensa");
Hecho RAD_NORMAL  ( "La radiación es normal");
Hecho RAD_BAJA 	( "La radiación es baja, requiere luz");
//Hecho DIA_NORMAL( "El día es un día normal"
Hecho DIA_NUBLADO ( "El día está nublado");
Hecho DIA_SOLEADO	( "El día está soleado");
Hecho SIN_LUZ_NATU( "se recibe luz natural");
Hecho OSCURO	( "Está oscuro");
Hecho BOMBA_NF	( "La bomba no funciona");
Hecho BOMBA_ON	( "La bomba está prendida");
Hecho BOMBA_OFF	( "La bomba está apagada");
Hecho WIFI_LOST	( "No hay señal de internet");
Hecho COMUN_LOST	( "No hay comunicación");
Hecho DANGER	( "Posible estado de emergencia");
Hecho PER_ABIERTA	( "Persiana abierta");
Hecho PER_CERRADA	( "Persiana cerrada");
Hecho PER_STOP	( "Persiana no se cierra ni abre");
Hecho PER_MOVE	( "Persiana se esta moviendo");
Hecho CERRAR_PER	( "Empezar a cerrar persiana");
Hecho ABRIR_PER	( "Empezar a mover persiana");
Hecho VENTIL_ON	( "Ventilador prendido");
Hecho VENTIL_OFF	( "Ventilador apagado");
Hecho VENTIL_NF   ( "Ventilador no funciona");
Hecho ILUM_ON 	( "Iluminación prendida");
Hecho ILUM_OFF	( "Iluminación apagada");

Regla regla3("Bomba no funciona", Operadores::AND, &BOMBA_NF);
Regla regla1("Prender la bomba", Operadores::AND, &BOMBA_ON);
Regla regla14("Bomba prendida, contradicción", Operadores::NOT, &BOMBA_ON);
Regla regla2("Apagar la bomba", Operadores::AND, &BOMBA_OFF);

Regla regla13("Ventilador no funciina", Operadores::AND, &VENTIL_NF);
Regla regla4("Prender ventilador", Operadores::AND, &VENTIL_ON);
Regla regla15("Oposicipón o negación", Operadores::NOT, &VENTIL_ON);
Regla regla5("Apagar ventilador", Operadores::AND, &VENTIL_OFF);
Regla regla10("Prender iluminación",Operadores::AND, &ILUM_ON);
Regla regla17("Control oposición de iluminacion", Operadores::NOT, &ILUM_ON);
Regla regla16("Aoagar iluminacion", Operadores::AND, &ILUM_OFF);