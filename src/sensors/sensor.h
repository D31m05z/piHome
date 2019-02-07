#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

class Sensor
{
public:
    Sensor() {}
    ~Sensor() {}

    virtual void update() = 0;
};
