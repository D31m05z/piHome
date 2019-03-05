#include "pihome/sensors/ipcamera.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace pihome::sensors;

IPCamera::IPCamera(const std::string& name, size_t width, size_t height)
    : Sensor(name)
    , Camera(width, height, width * height * 3) // TODO: w*h*c channel = 3 (RGB)
{
    // create server socket
}

IPCamera::~IPCamera()
{
}

void IPCamera::update()
{
    //capture
    // TODO: network interface

    std::lock_guard<std::mutex> guard(mutex_);

    //extract the image in rgb format
    // TODO: copy image image_.data.data(),  //get camera image
}

