#include "Arduino.h"
#include "string.h"

/*
typedef bool (*CambioValor)(void);
  CambioValor funcionCambio;
  typedef void (*CambioEstado)(void);
  CambioEstado funcionEstadoTrue;
  CambioEstado funcionEstadoFalso;
*/

enum KEYS_ACT{
    OK=0, FALLO=-1
};

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
