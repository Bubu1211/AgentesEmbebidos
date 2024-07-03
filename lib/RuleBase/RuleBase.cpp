
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
void RuleBase::chain()
{
    if(tamReglas == -1)
        return;
    
    for(int i = 0; i<=tamReglas; i++)
        reglas[i].evaluar();
}