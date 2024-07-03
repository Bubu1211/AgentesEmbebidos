#ifndef PIN_H
#define PIN_H
#include "Arduino.h"

class Pin{
    protected:
        int gpio;

    public:

        class Analog;
        class Digital;

        Pin(int gpio, int tipo);

        virtual int read() const
        {
            return -1;
        }
        virtual void write(int valor) const{}

        static Analog* analog(int gpio, int tipo);
        static Digital* digital(int gpio, int tipo);
};

class Pin::Analog : public Pin{

    public:
        Analog(int gpio, int tipo) : Pin(gpio, tipo){}

        virtual int read() const override{
        return analogRead(this->gpio);
        }

        virtual void write(int value) const override{
            analogWrite(this->gpio, value);
        }
};

class Pin::Digital : public Pin{

    public:
        Digital(int gpio, int tipo) : Pin(gpio, tipo){}

        virtual int read() const override{
        return digitalRead(this->gpio);
        }

        virtual void write(int value) const override{
            digitalWrite(this->gpio, value);
        }
};

#endif