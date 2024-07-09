#include "Arduino.h"
#include <BaseHechos.h>
#include <RuleBase.h>
#include <Pin.h>
#include <DHTesp.h>
#include <Wire.h>
#include <BH1750.h>
#include <ESP32Servo.h>
#include <MQTTWIFI.h>

#define PIN_DHT 14
#define SCL 22
#define SDA 21
#define SERVO_PERSIANA 23

/*Objetos y variables globales*/
RuleBase baseReglas("SExperto controlador de invernadero"); // SE conformado por una base de reglas
DHTesp dht;
BH1750 sensor_luz;
Servo persiana;
MQTTWiFi mqtt_wifi;
float lecturaHumTierra, lecturaTemperatura, lecturaLuz;
float HUMEDAD_MINIMA = 30, TEMPERATURA_MINIMA = 27.5, TEMPERATURA_MAXIMA = 29;
float LUZ_INTENSA = 3000, LUZ_BAJA = 300, LUZ_NONATURAL = 200;
int NG_PER_ABIERTA = 50, NG_PER_CERRADA = 0;

/* Pines necesarios*/
Pin *pHumTierra = Pin::analog(32, INPUT);
Pin *bomba = Pin::digital(18, OUTPUT);
Pin *ventilador = Pin::digital(19, OUTPUT);
Pin *ilum = Pin::digital(33, OUTPUT);

/*Dosfunciones necesarias para activar las variables
y para producir un efecto*/
void activacion()
{
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
  if (BOMBA_NF.valor)
    Serial.println(" La bomba no funciona, debe ser revisada");
  if (BOMBA_ON.valor)
    bomba->write(HIGH);
  if (BOMBA_OFF.valor)
    bomba->write(LOW);
  if (ILUM_ON.valor)
    ilum->write(HIGH);
  if (ILUM_OFF.valor)
    ilum->write(LOW);
  if (VENTIL_ON.valor)
    ventilador->write(HIGH);
  if (VENTIL_OFF.valor)
    ventilador->write(LOW);
  if (CERRAR_PER.valor)
    persiana.write(NG_PER_CERRADA);
  if (ABRIR_PER.valor)
    persiana.write(NG_PER_ABIERTA);
}

void setup()
{
  //Comunicación con el monitor serie
  Serial.begin(115200);
  //Se crean las reglas, con sus antecedentes correspondientes
  setup_base_reglas(&baseReglas);
  baseReglas.setActivacion(activacion);       //Se asigna la función que activa las reglas
  baseReglas.setEfecto(efecto);               //Se asigna la función que ejecuta los efectos de que los hechos se cumplan

  //Configuración de los sensores: DHT11, BH1750 y el servo de
  dht.setup(PIN_DHT, DHTesp::DHT11);
  Wire.begin(SDA, SCL);
  sensor_luz.begin();
  persiana.attach(SERVO_PERSIANA);
  //Estado inicial para verificar que los actuadores funcionan
  Serial.println("Inicio....");
  bomba->write(HIGH);
  persiana.write(NG_PER_ABIERTA);
  delay(3000);
  persiana.write(NG_PER_CERRADA);
  bomba->write(LOW);
  ilum->write(LOW);
  ventilador->write(LOW);
  Serial.println("Inciando programa");
  delay(3000);
}

void loop()
{
  lecturaHumTierra = map(pHumTierra->read(), 0, 4095, 100, 0);
  lecturaTemperatura = dht.getTemperature();
  lecturaLuz = sensor_luz.readLightLevel();
  Serial.printf("\n Lectura de humedad: %f | Lectura de temperatura: %f | lectura sensor de luz: %f\n",
                lecturaHumTierra, lecturaTemperatura, lecturaLuz);
  //La reglas son encadenadas
  baseReglas.chain();       
  delay(2000);
}