#include <Regla.h>
#include <Hecho.h>
#include <Consecuente.h>
#include <Antecedente.h>
#include <RuleBase.h>


int boton1 = 5, boton2 = 33, boton3 = 32;
int rojo = 2, azul = 15, verde = 1;

RuleBase base("Base reglas");
//Antecedentes
Antecedente btn1("Led 1 "), btn2("Led 2 "), btn3("Led 3 ");
//Consecuentes
Consecuente *led1 = new Consecuente("LED 1 ");
Consecuente *led2 = new Consecuente("LED 2");
Consecuente *led3 = new Consecuente("Led 3");
//Reglas 
Regla regla1(Operadores::AND, led1), regla2(Operadores::AND, led2), regla3(Operadores::AND, led3);

bool btn1CV(){ return digitalRead(boton1); }
bool btn2CV(){ return digitalRead(boton2); }
bool btn3CV(){ return digitalRead(boton3); }

void ledsoff()
{
  digitalWrite(azul, LOW);
  digitalWrite(rojo, LOW);
  digitalWrite(verde, LOW);
}

void led1Off(){digitalWrite(rojo, LOW); }
void led1On(){
  ledsoff();
  digitalWrite(rojo, HIGH); 
}
void led2Off(){digitalWrite(azul, LOW); }
void led2On(){
  ledsoff();
  digitalWrite(azul, HIGH); 
  }
void led3Off(){digitalWrite(verde, LOW); }
void led3On(){
  ledsoff();
  digitalWrite(verde, HIGH);
   }

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

  led1->set_ejecucion(led1On);
  led2->set_ejecucion(led2On);
  led3->set_ejecucion(led3On);

  regla1.add_antecedente(btn1);
  regla1.add_antecedente(btn2);
  regla2.add_antecedente(btn3);
  regla2.add_antecedente(btn1);
  regla3.add_antecedente(btn3);
  regla3.add_antecedente(btn2);

  base.add_regla(&regla1);
  base.add_regla(&regla2);
  base.add_regla(&regla3);
}

void loop()
{
  
  base.chain();
  delay(10);
}