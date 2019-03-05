#pragma once

#include "sensor.h"
#include "camera.h"
#include <memory>

namespace raspicam {
    class RaspiCam;
}

namespace pihome {
    namespace sensors {

        class RaspiCamera : public Sensor, public Camera {
        public:
            // std::string name
            RaspiCamera(const std::string &name, size_t width, size_t height);

            ~RaspiCamera();

            // update camera sensor
            void update() override;

        private:
            // cmaera object
            std::unique_ptr<raspicam::RaspiCam> camera_;
        };

    } // sensors
} // pihome