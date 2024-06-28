#include <Regla.h>


int boton1 = 5, boton2 = 33, boton3 = 32;
int rojo = 2, azul = 15, verde = 1;

//Antecedentes
Hecho btn1("Led 1 "), btn2("Led 2 "), btn3("Led 3 ");
//Consecuentes
Hecho *led1 = new Hecho("LED 1 "), *led2 = new Hecho("LED 2"), *led3 = new Hecho("Led 3");
//Reglas 
Regla regla1(Operadores::AND, led1), regla2(Operadores::AND, led2), regla3(Operadores::AND, led3);

bool btn1CV(){ return digitalRead(boton1); }
bool btn2CV(){ return digitalRead(boton2); }
bool btn3CV(){ return digitalRead(boton3); }

void led1Off(){digitalWrite(rojo, LOW); }
void led1On(){digitalWrite(rojo, HIGH); }
void led2Off(){digitalWrite(azul, LOW); }
void led2On(){digitalWrite(azul, HIGH); }
void led3Off(){digitalWrite(verde, LOW); }
void led3On(){digitalWrite(verde, HIGH); }

void setup()
{
  Serial.begin(115200);

  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  pinMode(boton3, INPUT);
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);

  btn1.set_cambio_valor(btn1CV);
  btn2.set_cambio_valor(btn2CV);
  btn3.set_cambio_valor(btn3CV);

  led1->set_estados(led1On, led1Off);
  led2->set_estados(led2On, led2Off);
  led3->set_estados(led3On, led3Off);

  regla1.add_antecedente(btn1);
  regla1.add_antecedente(btn2);
  regla2.add_antecedente(btn3);
  regla2.add_antecedente(btn1);
  regla3.add_antecedente(btn3);
  regla3.add_antecedente(btn2);
}

void loop()
{
  regla1.evaluar();
  regla2.evaluar();
  regla3.evaluar();

  delay(10);
}