#include "DS18B20.h"

const int TEMP_UPDATE_TIME = 1000;

DS18B20::DS18B20(uint8_t oneWirePin) :
    ds_(OneWire(oneWirePin))
{
    
}

void DS18B20::detectTemperature(){
    byte data[2];
    ds_.reset();
    ds_.write(0xCC);
    ds_.write(0x44);
 
    if (millis() - lastUpdateTime_ > TEMP_UPDATE_TIME)
    {
        lastUpdateTime_ = millis();
        ds_.reset();
        ds_.write(0xCC);
        ds_.write(0xBE);
        data[0] = ds_.read();
        data[1] = ds_.read();
 
        temperature_ =  ((data[1] << 8) | data[0]) * 0.0625;
    }
}

float DS18B20::temperature()
{
    return temperature_;
}
