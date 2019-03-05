#include "pihome/sensors/camera.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <unistd.h>

Camera::Camera(size_t width, size_t height, size_t imageSize)
{
    // allocate memory
    image_.width = width;
    image_.height = height;
    image_.data.resize(imageSize);
    std::cout << "width = " << image_.width << " height = " << image_.height << std::endl;
}

Camera::~Camera()
{
}

Image Camera::getImage()
{
    std::lock_guard<std::mutex> guard(mutex_);
    return image_;
}

void Camera::takePicture()
{
    static int counter = 0;
    std::string fileName = "image_" + std::to_string(++counter) + ".ppm";
    std::ofstream outFile(fileName, std::ios::binary);
    outFile << "P6\n" << image_.width << " " << image_.height << " 255\n";
    outFile.write((char*)image_.data.data(), image_.data.size());
    std::cout << "Image saved at " << fileName << std::endl;
}
