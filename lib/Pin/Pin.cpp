#include "Pin.h"

Pin::Pin(int gpio, int tipo)
{
    this->gpio = gpio;
    pinMode(this->gpio, tipo);
}

Pin::Analog* Pin::analog(int gpio, int tipo)
{
    return new Analog(gpio, tipo);
}
Pin::Digital* Pin::digital(int gpio, int tipo)
{
    return new Digital (gpio, tipo);
}  