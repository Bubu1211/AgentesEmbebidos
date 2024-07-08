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
Hecho::Hecho(String nombre)
{
    this->nombre = nombre;
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

String Hecho::toString()
{
    String text = "Consecuente "+getNombre()+" = ";
    text = text + valor;
    text = text + ";";
    return text;

}