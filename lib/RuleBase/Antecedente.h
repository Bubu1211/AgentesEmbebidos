#include "Arduino.h"
#include "string.h"
#include <Hecho.h>


class Antecedente : public Hecho{
    private:
        typedef bool (*Funcion)(void);
        Funcion cambiar_valor;

    public:
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
                return KEYS_ACT::FALLO;
            
            this->valor = this->cambiar_valor();
            return KEYS_ACT::OK;
        }
};