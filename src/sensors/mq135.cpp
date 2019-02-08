#include "mq135.h"
#include <wiringPi.h>

MQ135Sensor::MQ135Sensor(const std::string& name, int GAS_PIN)
    : Sensor(name)
    , GAS_PIN_(GAS_PIN)
    , detected_(false)
{
   pinMode(GAS_PIN_, INPUT);
}

MQ135Sensor::~MQ135Sensor()
{
}

void MQ135Sensor::update()
{
    if(digitalRead(GAS_PIN_) == LOW) {
        detected_ = true;
    } else {
        detected_ = false;
    }

    warning_ = detected_;
}
