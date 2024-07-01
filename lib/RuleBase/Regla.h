#include "Arduino.h"
#include "string.h"
#include <Antecedente.h>
#include <Consecuente.h>

enum Operadores
{
  AND = 0,
  OR = 1,
  NOT = 2
};

bool op_and(Antecedente *a, Antecedente *b)
{
  return a->get_valor() && b->get_valor();
}

bool op_or(Antecedente *a, Antecedente *b)
{
  return a->get_valor() || b->get_valor();
}

bool op_not(Antecedente *a, Antecedente *b)
{
  return !b->get_valor();
}


class Regla
{
private:
  Antecedente *antecedentes;
  Operadores operador;
  Consecuente *consecuente;
  int tamAntecedentes;
  typedef bool (*Operandos)(Antecedente *a, Antecedente *b);
  Operandos opFuncion;

public:
  Regla(Operadores op, Consecuente *c)
  {
    tamAntecedentes = 0;
    set_operador(op);
    consecuente = c;
  }

  void set_consecuente(Consecuente *consecuente)
  {
    this->consecuente = consecuente;
  }
  void set_operador(Operadores operador)
  {
    this->operador = operador;
    switch (this->operador)
    {
    case Operadores::AND: opFuncion = op_and;
      break;
    case Operadores::OR: opFuncion = op_or;
      break;
    case Operadores::NOT: opFuncion = op_not;
      break;
  }
}

  void add_antecedente(Antecedente a)
  {
    if (tamAntecedentes >= 9)
      return;

    /*if(antecedentes == nullptr)
      return;*/

    tamAntecedentes++;
    antecedentes[tamAntecedentes - 1] = a;
  }

  void set_antecedentes(Antecedente a[], int tam)
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
      antecedentes[i].activacion();
      antecedentes[i - 1].activacion();
      verdadero = opFuncion(&antecedentes[i], &antecedentes[i-1]);
    }
    if(verdadero) 
      consecuente->ejecutar();
    else  
      consecuente->no_activado();
  }
};