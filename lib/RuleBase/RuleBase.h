#include <Regla.h>
#ifndef RULEBASE_H
#define RULEBASE_H

class RuleBase{
    private:
        typedef void (*Funcion)(void);
        Funcion activacion;
        Funcion efecto;
        Regla reglas[20];
        String nombre;
        int tamReglas;

    public:
        RuleBase(String);
        void addRegla(Regla);
        template <typename T, typename...Args>
        void addReglas(T,Args...);
        void addReglas();
        void chain();
        void setActivacion(Funcion);
        void setEfecto(Funcion);
        String toString();
};

 template <typename T, typename...Args>
void RuleBase::addReglas(T r,Args...args)
{
    reglas[++tamReglas] = r;
    addReglas(args...);
}

#endif