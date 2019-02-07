#include "pir.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "wiringPi.h"

PIRSensor::PIRSensor(const std::string& name, int PIR_PIN)
    : Sensor(name)
    , PIR_PIN_(PIR_PIN)
{
    pinMode(PIR_PIN_, INPUT); // set pin PIR_PIN as input

    // we need to activate the pull-up resistor to
    // make use of this specific PIR sensor
    pullUpDnControl(PIR_PIN_, PUD_UP);
}

PIRSensor::~PIRSensor()
{

}

void PIRSensor::update()
{
    // read the value
    // 1 means no movement
    // 0 means that something is moving
    int val = digitalRead(PIR_PIN_);
    if(val == LOW) {
        printf("Motion detected %d\n", val);
    }
    //usleep(100000); // 10fps
}
