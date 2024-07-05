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
    
    Serial.print("Consecuente: ");
  Serial.print(this->consecuente->getNombre());
  Serial.print(" valor : ");
  Serial.print(this->consecuente->valor);
  if(this->operador == Operadores::NOT)
    this->consecuente->valor = !antecedentes[0]->valor;
  else
    this->consecuente->valor = antecedentes[0]->valor;
  Serial.print(" | AHORA: ");
  Serial.println(this->consecuente->valor);
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
  Serial.print("Consecuente: ");
  Serial.print(this->consecuente->getNombre());
  Serial.print(" valor : ");
  Serial.print(this->consecuente->valor);
  this->consecuente->valor = verdadero;
  Serial.print(" | AHORA: ");
  Serial.println(this->consecuente->valor);
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