#include "dht11.h"

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>  // memset

using namespace pihome::sensors;

DHT11Sensor::DHT11Sensor(const std::string& name, int DHT_PIN, int MAX_TIMINGS)
    : Sensor(name)
    , DHT_PIN_(DHT_PIN)
    , MAX_TIMINGS_(MAX_TIMINGS)
{
    memset(data_, 0, sizeof(data_));
}

DHT11Sensor::~DHT11Sensor()
{
}

void DHT11Sensor::update()
{
    uint8_t laststate   = HIGH;
    uint8_t counter     = 0;
    uint8_t j           = 0, i;

    //memset(data_, 0, sizeof(data_));
    data_[0] = data_[1] = data_[2] = data_[3] = data_[4] = 0;

    /* pull pin down for 18 milliseconds */
    pinMode( DHT_PIN_, OUTPUT );
    digitalWrite( DHT_PIN_, LOW );
    delay( 18 );

    /* prepare to read the pin */
    pinMode( DHT_PIN_, INPUT );

    /* detect change and read data */
    for ( i = 0; i < MAX_TIMINGS_; i++ ) {
        counter = 0;
        while ( digitalRead( DHT_PIN_ ) == laststate ) {
            counter++;
            delayMicroseconds( 1 );
            if ( counter == 255 ) {
                break;
            }
        }
        laststate = digitalRead( DHT_PIN_ );

        if ( counter == 255 )
            break;

        /* ignore first 3 transitions */
        if ( (i >= 4) && (i % 2 == 0) ) {
            /* shove each bit into the storage bytes */
            data_[j / 8] <<= 1;
            if ( counter > 16 ){
                data_[j / 8] |= 1;
            }
            j++;
        }
    }

    /*
     * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
     * print it out if data is good
     */
    if ( (j >= 40) &&
         (data_[4] == ( (data_[0] + data_[1] + data_[2] + data_[3]) & 0xFF) ) ) {
        float h = (float)((data_[0] << 8) + data_[1]) / 10;
        if ( h > 100 ) {
            h = data_[0];    // for DHT11
        }
        float c = (float)(((data_[2] & 0x7F) << 8) + data_[3]) / 10;
        if ( c > 125 ) {
            c = data_[2];    // for DHT11
        }
        if ( data_[2] & 0x80 ) {
            c = -c;
        }
        float f = c * 1.8f + 32;
        printf( "Humidity = %.1f %% Temperature = %.1f *C (%.1f *F)\n", h, c, f );
    } else  {
        printf( "Data not good, skip\n" );
    }
}
