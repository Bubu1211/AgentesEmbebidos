
#include <Pin.h>    //Librería adicional 
#include <Hecho.h>

//constantes predefinidas pra los GPIO
#define PIN_BOTON1 5
#define PIN_BOTON2 33
#define PIN_BOTON3 32
#define PIN_ROJO 2
#define PIN_AZUL 4
#define PIN_VERDE 15

//pines de los botones
Pin* boton1 = Pin::digital(PIN_BOTON1, INPUT);
Pin* boton2 = Pin::digital(PIN_BOTON2, INPUT);
Pin* boton3 = Pin::digital(PIN_BOTON3, INPUT);
//Pines de los leds
Pin* rojo  = Pin::digital(PIN_ROJO, OUTPUT);
Pin* azul  = Pin::digital(PIN_AZUL, OUTPUT);
Pin* verde = Pin::digital(PIN_VERDE, OUTPUT);

//Hechos de verdad
Hecho hb1("Boton 1", 1), hb2("Boton 2", 2), hb3("Boton 3", 3);
Hecho a("Led 1", 4), b("Led 2", 5), c("Led 3", 8); 

/*función de activación, al ejecutarse, da su correspondiente valor de verdad a 
//cada Hecho*/
void activacion()
{
  hb1.valor = boton1->read();
  hb2.valor = boton2->read();
  hb3.valor = boton3->read();
  Serial.printf("Boton 1: %d | boton 2: %d | boton 3: %d \n", hb1.valor, hb2.valor, hb3.valor);
}

/**Funcion de cambio o efecto */
void efecto()
{

  //Esto lo hacen las reglas
  a.valor = hb1.valor && hb2.valor;
  b.valor = hb1.valor && hb3.valor;
  c.valor = hb2.valor && hb3.valor;
  
  Serial.printf("Rojo 1: %d | verde 2: %d | azul 3: %d \n", a.valor, b.valor, c.valor);

  if(a.valor)
    rojo->write(HIGH);
  
  if(b.valor)
    verde->write(HIGH);

  if(c.valor)
    azul->write(HIGH);

}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  activacion();
  efecto();
  delay(1000);
}