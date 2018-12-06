#ifndef TempAlgorithm_h
#define TempAlgorithm_h

#include <Arduino.h>

#include "RelayAlgorithm.h"
#include "DS18B20.h"

class TempAlgorithm
{
public:
    TempAlgorithm(RelayAlgorithm *algorithm, DS18B20 *DS18B20Sensor);

    void tick();
    void start(int tempMin, int tempMax);
    void stop();
    bool isRunning();
    
private:
    enum AlgorithmState {
        HEAT_STATE,
        COOl_DOWN_STATE
    } currentState_ = HEAT_STATE;

    RelayAlgorithm *algorithm_;
    DS18B20 *DS18B20Sensor_;

    bool isRunning_ = false;

    int tempMin_ = 0;
    int tempMax_ = 0;
    
    uint32_t algorithmTimeStart_ = 0;
    uint32_t algorithmTimeEnd_ = 0;
};

#endif

