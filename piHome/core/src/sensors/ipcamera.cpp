#include "pihome/sensors/ipcamera.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace pihome::sensors;

IPCamera::IPCamera(const std::string& name, const char* address, int port, size_t width, size_t height)
    : Sensor(name)
    , Camera(width, height, width * height * 3) // TODO: w*h*c channel = 3 (RGB)
    , socket_(-1)
{
    // connect to server'
    socket_ = client_.createSocket(address, port);
}

IPCamera::~IPCamera()
{
}

void IPCamera::update()
{
    //capture
    std::vector<unsigned char> data;
    client_.receiveImage(socket_, data);

    std::lock_guard<std::mutex> guard(mutex_);

    // TODO: separate raw image and jpeg image recev
    //char* img;
    //int w, h, c;

    //STBIDEF stbi_uc *stbi_load_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp)
    //img = (char*)stbi_load_from_memory(data.data(), data.size(), &w, &h, &c, 3);

    //printf("w=%d h=%d c=%d\n", w, h, c);

    // TODO : eliminate the memcpy
    //image_.width = w;
    //image_.height = h;
    //image_.data.resize(w*h*c);
    //memcpy(image_.data.data(), img, image_.data.size());

    image_.width = 1280;
    image_.height= 720;
    image_.data = data;
}
