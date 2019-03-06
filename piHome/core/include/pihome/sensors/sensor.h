#pragma once

#include <string>

namespace pihome {
    namespace sensors {

        class Sensor {
        public:
            Sensor(const std::string &name)
                    : name_(name), warning_(false) {
            }

            ~Sensor() {}

            // update sensor
            virtual void update() = 0;

            // return the sensor name
            std::string name() { return name_; }

            bool getWarning() const { return warning_; }

        protected:
            // sensor name
            std::string name_;
            bool warning_;
        };

    } // sensors
} // pihome