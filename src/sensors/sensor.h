#include <string>

class Sensor
{
public:
    Sensor(const std::string& name) : name_(name) {}
    ~Sensor() {}

    // update sensor
    virtual void update() = 0;

    // return the sensor name
    std::string name() { return name_; }

protected:
    // sensor name
    std::string name_;
};
