#ifndef HECHO_H
#define HECHO_H

#include "Arduino.h"
#include "string.h"


class Hecho{
    private:
        String nombre;
        int id;
        //RuleBase *base;
    public:
        bool valor;
        Hecho(String, int);
        Hecho(String);
        String getNombre();
        String toString();
        int getId();
};

#endif