#include "Arduino.h"
#include "string.h"
#include <Antecedente.h>
#include <Consecuente.h>
#include <Regla.h>

class RuleBase{
    private:
        Regla* reglas[50];
        int indice;
        String nombre;
    public:
        RuleBase(String nombre){
            this->nombre = nombre;
            indice = 0;
        }

        void add_regla(Regla *regla)
        {
            if(indice >=49)
                return;
            reglas[indice++] = regla;
        }

        void chain()
        {
            for(int i = 0; i<indice; i++)
                reglas[i]->evaluar();
        }
};