#include "Arduino.h"
#include "string.h"

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
