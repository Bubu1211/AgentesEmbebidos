#include "Regla.h"


Regla::Regla(String nombre, Operadores op, Hecho* consecuente)
{
    this->nombre = nombre;
    this->operador = op;
    this->consecuente = consecuente;
    tamAntecedentes = 0;
}

Regla::Regla()
{
    this->nombre = "nombre";
    this->operador = Operadores::THEN;
    this->consecuente = NULL;
    tamAntecedentes = 0;
}

void Regla::evaluar()
{
 bool verdadero;
    for (int i = 1; i < tamAntecedentes; i++)
    {
      switch (operador)
      {
      case AND: 
        verdadero = antecedentes[i]->valor && antecedentes[i - 1]->valor;
        break;
      case OR: 
        verdadero = antecedentes[i]->valor || antecedentes[i - 1]->valor;
        break;
      case NOT: 
        verdadero = !antecedentes[i - 1]->valor;
        break;
      }
    }
    this->consecuente->valor = verdadero;
}
void Regla::addHecho(Hecho *h)
{
  antecedentes[tamAntecedentes++] = h;
}

void Regla::addHechos(){}

void Regla::setConsecuente(Hecho *h)
{
    this->consecuente = h;
}