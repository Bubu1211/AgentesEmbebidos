#include "Hecho.h"

/*
El estado inicial del sistema es que ninguna variable esta activa
*/
Hecho::Hecho(String nombre, int id)
{
    this->nombre = nombre;
    this->id = id;
    this->valor = false; 
}
String Hecho::getNombre()
{
    return this->nombre;
}
int Hecho::getId()
{
    return this->id;
}