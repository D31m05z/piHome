#include <string>

class Sensor
{
public:
    Sensor() {}
    ~Sensor() {}

    // update sensor
    virtual void update() = 0;

    // return the sensor name
    std::string name() { return name_; }

protected:
    // sensor name
    std::string name_;
};
