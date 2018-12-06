#ifndef TimeAlgorithm_h
#define TimeAlgorithm_h

#include <Arduino.h>

#include "RelayAlgorithm.h"

class TimeAlgorithm
{
public:
    TimeAlgorithm(RelayAlgorithm *algorithm);

    void tick();
    void start(uint32_t sleepMs);
    void stop();
    bool isRunning();
    
private:
    RelayAlgorithm *algorithm_;

    bool isRunning_ = false;
    
    uint32_t algorithmTimeStart_ = 0;
    uint32_t algorithmTimeEnd_ = 0;
};

#endif
