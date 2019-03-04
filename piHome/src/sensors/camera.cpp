#include "camera.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

CameraSensor::CameraSensor(const std::string& name)
    : Sensor(name)
{
    //Open camera
    std::cout << "Opening Camera..." << std::endl;
    if (!camera_.open()) {
        throw std::runtime_error("Error opening the camera sensor.");
    }

    //wait a while until camera stabilizes
    std::cout << "Sleeping for 3 secs" << std::endl;
    usleep(3*1000000);

    //capture
    camera_.grab();

    // allocate memory
    image_.width = camera_.getWidth();
    image_.height = camera_.getHeight();
    image_.data.resize(camera_.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
    std::cout << "width = " << image_.width << " height = " << image_.height << std::endl;
}

CameraSensor::~CameraSensor()
{
}

void CameraSensor::update()
{
    //capture
    camera_.grab();

    std::lock_guard<std::mutex> guard(mutex_);

    //extract the image in rgb format
    camera_.retrieve(image_.data.data(), raspicam::RASPICAM_FORMAT_RGB); //get camera image
}

RaspiImage CameraSensor::getImage()
{
    std::lock_guard<std::mutex> guard(mutex_);
    return image_;
}

void CameraSensor::takePicture()
{
    static int counter = 0;
    std::string fileName = "image_" + std::to_string(++counter) + ".ppm";
    std::ofstream outFile(fileName, std::ios::binary);
    outFile << "P6\n" << camera_.getWidth() << " " << camera_.getHeight() << " 255\n";
    outFile.write((char*)image_.data.data(), camera_.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
    std::cout << "Image saved at " << fileName << std::endl;
}
