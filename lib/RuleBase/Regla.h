#include "Arduino.h"
#include "string.h"
#include "Hecho.h"

enum Operadores
{
  AND = 0,
  OR = 1,
  NOT = 2
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