#include "Arduino.h"
#include <BaseHechos.h>
#include <RuleBase.h>
#include <Pin.h>
#include <DHTesp.h>
#include <Wire.h>
#include <BH1750.h>
#include <ESP32Servo.h>

#define PIN_DHT 14
#define SCL 22
#define SDA 21  
#define SERVO_PERSIANA 23

/*
Objetos y variables globales
*/
RuleBase baseReglas("SExperto controlador de invernadero");   //SE conformado por una base de reglas 
DHTesp dht;
BH1750 sensor_luz;
Servo persiana;
float lecturaHumTierra;
float lecturaTemperatura;
float lecturaLuz;
float HUMEDAD_MINIMA = 30;
float TEMPERATURA_MINIMA = 27.5;
float TEMPERATURA_MAXIMA = 29;
float LUZ_INTENSA = 3000;
float LUZ_BAJA = 300;
float LUZ_NONATURAL = 200;
int NG_PER_ABIERTA = 50;
int NG_PER_CERRADA = 0;


/*
  Pines necesarios
*/
Pin* pHumTierra = Pin::analog(32, INPUT);
Pin* bomba      = Pin::digital(18, OUTPUT);
Pin* ventilador = Pin::digital(19, OUTPUT);
Pin* ilum       = Pin::digital(33, OUTPUT);

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
  lecturaLuz = sensor_luz.readLightLevel();
  Serial.printf("\n lectura sensor de luz: %f", lecturaLuz);

  TIERRA_HUM.valor = lecturaHumTierra >= HUMEDAD_MINIMA;
  TIERRA_SECA.valor = lecturaHumTierra < HUMEDAD_MINIMA;
  TEMP_ALT.valor = lecturaTemperatura >= TEMPERATURA_MAXIMA;
  TEMP_BAJA.valor = lecturaTemperatura <= TEMPERATURA_MINIMA;
  TEMP_NORMAL.valor = lecturaTemperatura > TEMPERATURA_MINIMA && lecturaTemperatura < TEMPERATURA_MAXIMA;
  SIN_LUZ_NATU.valor = lecturaLuz < LUZ_NONATURAL;
  RAD_INT.valor = lecturaLuz >= LUZ_INTENSA;
  RAD_BAJA.valor = lecturaLuz < LUZ_BAJA;

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
  if(CERRAR_PER.valor){
    persiana.write(NG_PER_CERRADA);
    Serial.println("Vneitlador apagado");
  }
  if(ABRIR_PER.valor){
    persiana.write(NG_PER_ABIERTA);
    Serial.println("Vneitlador apagado");
  }
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

  regla1.addHechos(&TIERRA_HUM);
  regla2.addHechos(&TIERRA_SECA);
  regla3.addHechos(&TEMP_ALT);
  regla4.addHechos(&TEMP_BAJA);
  regla5.addHechos(&ILUM_ON);
  regla6.addHechos(&VENTIL_ON);
  regla7.addHechos(&TEMP_NORMAL);
  regla8.addHechos(&TEMP_NORMAL);
  regla9.addHechos(&RAD_INT);
  regla10.addHechos(&RAD_BAJA);
  regla12.addHechos(&SIN_LUZ_NATU);
  regla13.addHechos(&TEMP_BAJA);
  baseReglas.addReglas(
    regla1, regla2, regla3, regla4,regla13, regla5, regla6,
     regla7, regla8, regla9, regla10
  );
  baseReglas.setActivacion(activacion);
  baseReglas.setEfecto(efecto);
}

void setup()
{
  Serial.begin(115200);
  setup_base_reglas();
  dht.setup(PIN_DHT, DHTesp::DHT11);
  Wire.begin(SDA, SCL);
  sensor_luz.begin();
  persiana.attach(SERVO_PERSIANA);

  Serial.println("Inicio....");
  bomba->write(HIGH);
  ilum->write(HIGH);
  ventilador->write(HIGH);
  persiana.write(NG_PER_ABIERTA);
  persiana.write(NG_PER_CERRADA);
  delay(3000);
  bomba->write(LOW);

  Serial.println("Inciando programa");
  
  delay(3000);
}

void loop()
{
  baseReglas.chain();
  delay(2000);
}