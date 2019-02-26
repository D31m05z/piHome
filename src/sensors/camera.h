#pragma once

#include "sensor.h"
#include <raspicam/raspicam.h>
#include <vector>
#include <mutex>

struct RaspiImage
{
    int width = 0;
    int height = 0;
    std::vector<uint8_t> data;
};

class CameraSensor : public Sensor
{
public:
    // std::string name
    CameraSensor(const std::string& name);
    ~CameraSensor();

    // update camera sensor
    void update() override;

    RaspiImage getImage();
    void takePicture();

private:
    // cmaera object
    raspicam::RaspiCam camera_;
    RaspiImage image_;
    std::mutex mutex_;
};
