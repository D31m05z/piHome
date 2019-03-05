#pragma once

#include <vector>
#include <mutex>

struct Image
{
    int width = 0;
    int height = 0;
    std::vector<uint8_t> data;
};

class Camera
{
public:
    Camera(size_t width, size_t height, size_t imageSize);
    ~Camera();

    Image getImage();
    void takePicture();

protected:
    Image image_;
    std::mutex mutex_;
};
