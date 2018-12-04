#ifndef TimerRelay_h
#define TimerRelay_h

#include <Arduino.h>

class TimerRelay
{
public:
    TimerRelay(uint8_t relayPin);

    void begin();
    void tick();
    void start(uint32_t sleepMs);
    
private:
    bool isRunning_ = false;
    uint8_t relayPin_ = 0;
    uint32_t sleepMs_ = 900;
    uint32_t timeStarted_ = 0;
};

#endif
