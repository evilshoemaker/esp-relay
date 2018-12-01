#ifndef DS18B20_h
#define DS18B20_h

#include <OneWire.h>

class DS18B20
{
public:
    DS18B20(uint8_t oneWirePin);
    void detectTemperature(); 
    float temperature();
    
private:
    OneWire ds_;
    uint32_t lastUpdateTime_ = 0;
    int temperature_ = 0;
};

#endif
