#pragma once

#include "pihome/sensors/sensor.h"
#include "pihome/sensors/camera.h"
#include "pihome/networks/client.h"

#include <vector>
#include <mutex>

namespace pihome {
    namespace sensors {

        class IPCamera : public Sensor, public Camera {
        public:
            // std::string name
            IPCamera(const std::string &name, size_t width, size_t height);

            ~IPCamera();

            // update camera sensor
            void update() override;

        private:
            networks::Client client_;
            int socket_;
        };

    } // sensors
} // pihome