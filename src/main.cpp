#include "Arduino.h"
#include "string.h"

enum Operadores
{
  AND = 0,
  OR = 1,
  NOT = 2
};

class Hecho
{
public:
  String id;
  bool valor;
  typedef bool (*CambioValor)(void);
  CambioValor funcionCambio;
  typedef void (*CambioEstado)(void);
  CambioEstado funcionEstadoTrue;
  CambioEstado funcionEstadoFalso;

  Hecho()
  {
    valor = false;
  }

  Hecho(String id)
  {
    valor = false;
    this->id = id;
  }

  void set_cambio_valor(CambioValor cambio)
  {
    this->funcionCambio = cambio;
  }

  void set_funciones(CambioValor cambioValor, CambioEstado ct, CambioEstado cf)
  {
    this->funcionCambio = cambioValor;
    this->funcionEstadoTrue = ct;
    this->funcionEstadoFalso = cf;
  }

  void set_estados(CambioEstado verdad, CambioEstado falso)
  {
    this->funcionEstadoTrue = verdad;
    this->funcionEstadoFalso = falso;
  }

  void set_estado_true(CambioEstado ce)
  {
    this->funcionEstadoTrue = ce;
  }

  void set_estado_false(CambioEstado ce)
  {
    this->funcionEstadoFalso = ce;
  }

  void cambio_valor()
  {
    if (funcionCambio != nullptr)
    {
      Serial.print(" Cambio valor: ");
      Serial.print(id);
      this->valor = funcionCambio();
      Serial.print(" = ");
      Serial.println(valor);
    }
    else
    {
      Serial.println("Puntero a función vacio");
    }
  }

  void cambio_estado()
  {
    if (valor)
    {
      if (funcionEstadoTrue == nullptr)
        return;
      funcionEstadoTrue();
    }
    else
    {
      if (funcionEstadoFalso == nullptr)
        return;
      funcionEstadoFalso();
    }
  }
};

class Regla
{
public:
  Hecho antecedentes[10];
  Operadores operador;
  Hecho *consecuente;
  int tamAntecedentes;

  Regla(Operadores op, Hecho *c)
  {
    tamAntecedentes = 0;
    operador = op;
    consecuente = c;
  }

  void set_consecuente(Hecho *consecuente)
  {
    this->consecuente = consecuente;
  }
  void set_operador(Operadores operador)
  {
    this->operador = operador;
  }

  void add_antecedente(Hecho a)
  {
    if (tamAntecedentes >= 9)
      return;

    tamAntecedentes++;
    antecedentes[tamAntecedentes - 1] = a;
  }

  void set_antecedentes(Hecho a[], int tam)
  {
    if (tam > 10)
      return;
    tamAntecedentes = tam;
    for (int i = 0; i < tamAntecedentes; i++)
      antecedentes[i] = a[i];
  }
  void evaluar()
  {

    bool verdadero;
    for (int i = 1; i < tamAntecedentes; i++)
    {
      antecedentes[i].cambio_valor();
      antecedentes[i - 1].cambio_valor();

      switch (operador)
      {
      case AND:
        verdadero = antecedentes[i].valor && antecedentes[i - 1].valor;
        break;
      case OR:
        verdadero = antecedentes[i].valor || antecedentes[i - 1].valor;
        break;
      case NOT:
        verdadero = !antecedentes[i - 1].valor;
        break;
      }
    }
    this->consecuente->valor = verdadero;
    this->consecuente->cambio_estado();
  }
};

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