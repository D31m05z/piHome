#pragma once

#include "sensor.h"
#include <mutex>

namespace pihome {
    namespace sensors {
        struct DHTData {
 	    float humidity = 0.0f;
	    float temperature = 0.0f;
	    float temperature_f = 0.0f;
	};

        class DHT11Sensor : public Sensor {
        public:
            // std::string name
            // int DHT_PIN = 3   /* GPIO-22 */
            // int MAX_TIMINGS = 85
            DHT11Sensor(const std::string &name, int DHT_PIN, int MAX_TIMINGS);

            ~DHT11Sensor();

            // update sensor, read data from sensor
            void update() override;

	    DHTData getData();

        private:
            // GPIO pin
            int DHT_PIN_;
            // time of measuring data
            int MAX_TIMINGS_;
            // raw data from sensor
            int data_[5];

            DHTData dhtData_;
	    std::mutex mutex_;
        };

    } // sensors
} // pihome
