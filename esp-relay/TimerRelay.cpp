#include "TimerRelay.h"

TimerRelay::TimerRelay(int relayPin) :
    relayPin_(relayPin)
{
    
}

void TimerRelay::begin()
{
    pinMode(relayPin_, OUTPUT);
    digitalWrite(relayPin_, HIGH);
}

void TimerRelay::tick()
{
    if (isRunning_ && ((millis() - timeStarted_) > sleepMs_))
    {
        digitalWrite(relayPin_, HIGH);
        isRunning_ = false;
    }
}

void TimerRelay::start(uint32_t sleepMs)
{
    isRunning_ = true;
    sleepMs_ = sleepMs;
    digitalWrite(relayPin_, LOW);
    timeStarted_ = millis();
}
