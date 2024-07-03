#include <Regla.h>
#ifndef RULEBASE_H
#define RULEBASE_H

class RuleBase{
    private:
        Regla reglas[20];
        String nombre;
        int tamReglas;

    public:
        RuleBase(String);
        void addRegla(Regla);
        void chain();
};

#endif