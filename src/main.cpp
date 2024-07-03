
#include <Pin.h>

#define PIN_BOTON2 33
#define PIN_ROJO 2

int boton1 = 5, boton3 = 32;
int azul = 4, verde = 15;

Pin* boton2 = Pin::digital(PIN_BOTON2, INPUT);
Pin* rojo = Pin::digital(PIN_ROJO, OUTPUT);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  rojo->write(HIGH);
  delay(2000);
  rojo->write(LOW);
  delay(2000);
}