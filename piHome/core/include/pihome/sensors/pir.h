#pragma once

#include "sensor.h"
#include <time.h>

namespace pihome {
    namespace sensors {

        struct PIRData {
            struct tm *timeinfo = nullptr;
            bool detected = false;
            uint count = 0;
        };

        class PIRSensor : public Sensor {
        public:
            // std::string name
            // int PIR_PIN = 20   /* GPIO-20 */
            PIRSensor(const std::string &name, int PIR_PIN);

            ~PIRSensor();

            // update sensor, read data from sensor
            void update() override;

            // TODO: is not thread safe
            PIRData getData() { return data_; }

        private:
            // GPIO pin
            int PIR_PIN_;
            time_t rawtime_;
            PIRData data_;
        };

    } // sensors
} // pihome