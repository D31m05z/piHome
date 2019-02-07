#include "pir.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "wiringPi.h"

time_t rawtime;
struct tm * timeinfo;

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
    static int counter = 0;
    int val = digitalRead(PIR_PIN_);
    if(val == 1) {
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        printf("Current local time and date: %s", asctime (timeinfo));
        printf("Motion detected %d\n", ++counter);
    } else {
        // no movements
    }
}
