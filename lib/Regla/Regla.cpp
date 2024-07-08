#include "Regla.h"

Regla::Regla(String nombre, Operadores op, Hecho *consecuente)
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
  if (tamAntecedentes == 1)
  {
    if(this->operador == Operadores::NOT)
      this->consecuente->valor = !antecedentes[0]->valor;
    else
      this->consecuente->valor = antecedentes[0]->valor;
    return;
  }
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
}
void Regla::addHecho(Hecho *h)
{
  antecedentes[tamAntecedentes++] = h;
}

void Regla::addHechos() {}

void Regla::setConsecuente(Hecho *h)
{
  this->consecuente = h;
}

String Regla::toString()
{
  String text = "Regla = [";
  text = text + " nombre: "+this->nombre;
  text = text + " antecedentes: \n";
  for(int i = 0; i<tamAntecedentes; i++)
  {
    text = text + antecedentes[i]->toString() + "\n";
  }
  text = text + " Consecuente "+this->consecuente->toString()+"]";
  return text;
}