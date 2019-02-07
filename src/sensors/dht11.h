#include "sensor.h"

class DHT11Sensor : public Sensor
{
public:
    /// int DHT_PIN = 3   /* GPIO-22 */
    DHT11Sensor(int DHT_PIN);
    ~DHT11Sensor();

    void update() override;

private:
    int DHT_PIN_;
    int MAX_TIMINGS_;
    int data_[5];
}
