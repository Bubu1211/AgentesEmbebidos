
#include "RuleBase.h"

RuleBase::RuleBase(String nombre)
{
    this->nombre = nombre;
    tamReglas = -1;
}

void RuleBase::addRegla(Regla r)
{
    this->reglas[++tamReglas] = r;
}

void RuleBase::addReglas(){}

void RuleBase::chain()
{
    if(tamReglas == -1)
        return;

    if(activacion != nullptr)
        activacion();

    for(int i = 0; i<=tamReglas; i++)
        reglas[i].evaluar();

    if(efecto != nullptr)
        efecto();
}


void RuleBase::setActivacion(Funcion f)
{
    this->activacion = f;
}   

void RuleBase::setEfecto(Funcion f)
{
    this->efecto = f;
}

String RuleBase::toString()
{
    String text = "\nBase de reglas: "+this->nombre;
    for ( int i = 0; i<=this->tamReglas; i++)
    {
        text = text + reglas[i].toString();
    }
    return text + "\n";
}