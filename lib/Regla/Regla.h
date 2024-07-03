#include <Hecho.h>

#ifndef REGLA_H
#define REGLA_H

enum Operadores{
    AND = 0, OR = 1, NOT = 2, THEN = 3
};

class Regla{
    private:
        Hecho* antecedentes[10];
        Operadores operador;
        Hecho *consecuente;
        int tamAntecedentes;
        String nombre;
    
    public:
        Regla(String, Operadores, Hecho*);
        Regla();
        void evaluar();
        void addHecho(Hecho*);
        void setConsecuente(Hecho*);
};

#endif