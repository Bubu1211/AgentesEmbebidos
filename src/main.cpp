#include "Arduino.h"
#include <BaseHechos.h>
#include <RuleBase.h>
#include <Pin.h>
#include <DHTesp.h>

#define PIN_DHT 14

/*
Objetos y variables globales
*/
RuleBase baseReglas("SExperto controlador de invernadero");   //SE conformado por una base de reglas 
DHTesp dht;
float lecturaHumTierra;
float lecturaTemperatura;
float HUMEDAD_MINIMA = 30;
float TEMPERATURA_MINIMA = 25;
float TEMPERATURA_MAXIMA = 27;

/*
  Pines necesarios
*/
Pin* pHumTierra = Pin::analog(32, INPUT);
Pin* bomba      = Pin::digital(18, OUTPUT);
Pin* ventilador = Pin::digital(19, OUTPUT);
Pin* ilum       = Pin::digital(21, OUTPUT);

/*
Dosfunciones necesarias para activar las variables
y para producir un efecto
*/
void activacion()
{
  lecturaHumTierra = map(pHumTierra->read(), 0, 4095,100, 0);
  Serial.printf("\n Lectura de humedad: %f", lecturaHumTierra);
  lecturaTemperatura = dht.getTemperature();
  Serial.printf("\n Lectura de temperatura: %f", lecturaTemperatura);

  TIERRA_HUM.valor = lecturaHumTierra >= HUMEDAD_MINIMA;
  TIERRA_SECA.valor = lecturaHumTierra < HUMEDAD_MINIMA;
  TEMP_ALT.valor = lecturaTemperatura >= TEMPERATURA_MAXIMA;
  TEMP_BAJA.valor = lecturaTemperatura <= TEMPERATURA_MINIMA;


}

void efecto()
{
  Serial.printf("\n Bomba nf : %d | Bomba: %d | Bomba Off: %d \n", BOMBA_NF.valor, BOMBA_ON.valor, BOMBA_OFF.valor);
  if(BOMBA_NF.valor)
    Serial.println(" La bomba no funciona, debe ser revisada");

  if(BOMBA_ON.valor){
    bomba->write(HIGH);
    Serial.println("Prender bomba");
  }
  if(BOMBA_OFF.valor){
    
    bomba->write(LOW);
    Serial.println("Apagar bomba");
  }
  if(ILUM_ON.valor){
    ilum->write(HIGH);
    Serial.println("Iluminacion prendida");

  }
  if(ILUM_OFF.valor){
    ilum->write(LOW);
    Serial.println("Iluminacion APAGADA");

  }
  if(VENTIL_ON.valor){
    ventilador->write(HIGH);
    Serial.println("Vneitlador prendido");
  }
  if(VENTIL_OFF.valor){
    ventilador->write(LOW);
    Serial.println("Vneitlador apagado");
  }
    /*
  if(BOMBA_OFF.valor){
    bomba->write(LOW);
    
    Serial.println("Apagar bomba");
  }
    */
}

/*
Función que inicializa el sistema basado en reglas, empezando por 
agregar antecedentes a las reglas y luego se incluyen las reglas en la base de reglas
*/
void setup_base_reglas()
{
  //Estado inicial de algunos Hechos
  BOMBA_OFF.valor = true;
  ILUM_OFF.valor = true;
  VENTIL_OFF.valor = true;

  regla3.addHechos(&TIERRA_HUM, &BOMBA_ON);
  regla1.addHechos(&TIERRA_SECA, &BOMBA_OFF);
  regla14.addHechos(&BOMBA_OFF);
  regla2.addHechos(&TIERRA_HUM, &BOMBA_ON);
  baseReglas.addReglas(regla3, regla1, regla14, regla2);

  regla13.addHechos(&TEMP_ALT, &VENTIL_ON);
  regla4.addHechos(&TEMP_ALT, &VENTIL_OFF);
  regla15.addHechos(&VENTIL_OFF);
  regla5.addHechos(&TEMP_NORMAL, &VENTIL_ON);
  regla10.addHechos(&TEMP_BAJA, &ILUM_OFF);
  regla17.addHechos(&ILUM_OFF);
  regla16.addHechos(&TEMP_NORMAL, &ILUM_ON);
  baseReglas.addReglas(regla13, regla4, regla15, regla5, regla10, regla17, regla16);

  baseReglas.setActivacion(activacion);
  baseReglas.setEfecto(efecto);
}

void setup()
{
  Serial.begin(115200);
  setup_base_reglas();
  bomba->write(LOW);
  Serial.println("Inciando programa");
  dht.setup(PIN_DHT, DHTesp::DHT11);
  delay(3000);
}

void loop()
{
  baseReglas.chain();
  delay(2000);
}