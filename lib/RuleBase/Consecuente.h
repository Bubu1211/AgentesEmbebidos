#include "Arduino.h"
#include "string.h"
#include <Hecho.h>


class Consecuente : public Hecho{
    private:
        typedef void (*Funcion)(void);
        Funcion ejecucion;

    public:

        void set_ejecucion(Funcion funcion)
        {
            this->ejecucion = funcion;
        }

        Funcion get_ejecucion()
        {
            return this->ejecucion;
        }

        int ejecutar()
        {
            if(ejecucion == nullptr)
                return KEYS_ACT::FALLO;
            
            this->valor = true;
            this->ejecucion();
            return KEYS_ACT::OK;
        }

        void no_activado()
        {
            this->valor = false;
        }
};