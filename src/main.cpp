#include "Arduino.h"
#include <BaseHechos.h>
#include <RuleBase.h>
#include <Pin.h>

/*
Objetos y variables globales
*/
RuleBase baseReglas("SExperto controlador de invernadero");   //SE conformado por una base de reglas 
float lecturaHumTierra;
float HUMEDAD_MINIMA = 30;

/*
  Pines necesarios
*/
Pin* pHumTierra = Pin::analog(32, INPUT);
Pin* bomba      = Pin::digital(18, OUTPUT);

/*
Dosfunciones necesarias para activar las variables
y para producir un efecto
*/
void activacion()
{
  lecturaHumTierra = map(pHumTierra->read(), 0, 4095,100, 0);
  Serial.printf("\n Lectura de humedad: %f", lecturaHumTierra);

  TIERRA_HUM.valor = lecturaHumTierra >= HUMEDAD_MINIMA;
  TIERRA_SECA.valor = lecturaHumTierra < HUMEDAD_MINIMA;
  Serial.printf("\n hUMEDA : %d | Seca On: %d \n", TIERRA_HUM.valor, TIERRA_SECA.valor);
  Serial.printf("\n Bomba nf : %d | Bomba: %d | Bomba Off: %d \n", BOMBA_NF.valor, BOMBA_ON.valor, BOMBA_OFF.valor);
}

void efecto()
{
  Serial.printf("\n Bomba nf : %d | Bomba: %d | Bomba Off: %d \n", BOMBA_NF.valor, BOMBA_ON.valor, BOMBA_OFF.valor);
  if(BOMBA_NF.valor);
    Serial.println(" La bomba no funciona, debe ser revisada");

  if(BOMBA_ON.valor){
    bomba->write(HIGH);
    Serial.println("Prender bomba");
  }
  if(BOMBA_OFF.valor){
    
    bomba->write(LOW);
    Serial.println("Apagar bomba");
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

  regla3.addHechos(&TIERRA_HUM, &BOMBA_ON);
  regla1.addHechos(&TIERRA_SECA, &BOMBA_OFF);
  regla14.addHechos(&BOMBA_OFF);
  regla2.addHechos(&TIERRA_HUM, &BOMBA_ON);
  baseReglas.addReglas(regla3, regla1, regla14, regla2);

  baseReglas.setActivacion(activacion);
  baseReglas.setEfecto(efecto);
}

void setup()
{
  Serial.begin(115200);
  setup_base_reglas();
  bomba->write(LOW);
  Serial.println("Inciando programa");
  delay(3000);
}

void loop()
{
  baseReglas.chain();
  delay(2000);
}