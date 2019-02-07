#pragma once

#include "sensor.h"

class PIRSensor : public Sensor
{
public:
    // std::string name
    // int PIR_PIN = 20   /* GPIO-20 */
    PIRSensor(const std::string& name, int PIR_PIN);
    ~PIRSensor();

    // update sensor, read data from sensor
    void update() override;

private:
    // GPIO pin
    int PIR_PIN_;
};
