#include "mq135.h"
#include <wiringPi.h>

MQ135Sensor::MQ135Sensor(const std::string& name, int GAS_PIN)
	: Sensor(name)
	, GAS_PIN_(GAS_PIN)
{
   pinMode(GAS_PIN_, INPUT);
}

MQ135Sensor::~MQ135Sensor()
{
}

void MQ135Sensor::update()
{
    if(digitalRead(GAS_PIN_) == LOW) {
        printf("GAS detected\n");
    } else {
        printf("OK\n");
    }
}
