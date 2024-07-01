#ifndef Antecedente_H
#define Antecedente_H

#include "Arduino.h"
#include "string.h"
#include <Hecho.h>


class Antecedente : public Hecho{
    private:
        typedef bool (*Funcion)(void);
        Funcion cambiar_valor;

    public:

        Antecedente(String id)
        {
            this->id = id;
        }

        void set_cambio_valor(Funcion funcion)
        {
            this->cambiar_valor = funcion;
        }

        Funcion get_cambio_valor()
        {
            return this->cambiar_valor;
        }

        int activacion()
        {
            if(cambiar_valor == nullptr)
                return -1; //KEYS_ACT::FALLO;
            
            this->valor = this->cambiar_valor();
            return 0;//KEYS_ACT::OK;
        }
};

#endif