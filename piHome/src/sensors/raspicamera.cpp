#include "pihome/sensors/raspicamera.h"
#include <raspicam/raspicam.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace pihome::sensors;

RaspiCamera::RaspiCamera(const std::string& name, size_t width, size_t height)
    : Sensor(name)
    , Camera(width, height, width * height * 3) // TODO: w*h*c channel = 3 (RGB)
{
    camera_.reset(new raspicam::RaspiCam());
    camera_->setWidth(width);
    camera_->setHeight(height);

    //Open camera
    std::cout << "Opening Camera..." << std::endl;
    if (!camera_->open()) {
        throw std::runtime_error("Error opening the camera sensor.");
    }

    //wait a while until camera stabilizes
    std::cout << "Sleeping for 3 secs" << std::endl;
    usleep(3*1000000);

    //capture
    camera_->grab();

    if(image_.width != camera_->getWidth() ||
       image_.height != camera_->getHeight() ||
       image_.data.size() != camera_->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)) {
       printf("Wrong image sizes from camera: width %d!=%d height %d!=%d size %d!=%d", image_.width, camera_->getWidth(),
                                                                                       image_.height, camera_->getHeight(),
                                                                                       image_.data.size(), camera_->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
       throw std::runtime_error("Wrong image sizes from camera.");
    }
}

RaspiCamera::~RaspiCamera()
{
}

void RaspiCamera::update()
{
    //capture
    camera_->grab();

    std::lock_guard<std::mutex> guard(mutex_);

    //extract the image in rgb format
    camera_->retrieve(image_.data.data(), raspicam::RASPICAM_FORMAT_RGB); //get camera image
}
