#ifndef Hecho_H
#define Hecho_H

#include "Arduino.h"
#include "string.h"

/*
typedef bool (*CambioValor)(void);
  CambioValor funcionCambio;
  typedef void (*CambioEstado)(void);
  CambioEstado funcionEstadoTrue;
  CambioEstado funcionEstadoFalso;
*/


class Hecho
{

protected:
  String id;
  bool valor;
  
public:

  Hecho()
  {
    valor = false;
  }

  Hecho(String id)
  {
    valor = false;
    this->id = id;
  }

  void set_id(String id)
  {
    this->id = id;
  }

  String get_id()
  {
    return this->id;
  }

  bool get_valor()
  {
    return this->valor;
  }

  void set_Valor(bool valor)
  {
    this->valor = valor;
  }
};

#endif