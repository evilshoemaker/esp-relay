#include "TimeAlgorithm.h"

TimeAlgorithm::TimeAlgorithm(RelayAlgorithm *algorithm) :
    algorithm_(algorithm)
{
    
}

void TimeAlgorithm::tick()
{
    if (algorithm_->isRunning())
    {
        if ((millis() - algorithmTimeStart_) > algorithmTimeEnd_)
        {
            algorithm_->stop();
        }
    }
}

void TimeAlgorithm::start(uint32_t sleepMs)
{
    algorithmTimeEnd_ = sleepMs;
    algorithmTimeStart_ = millis();
    isRunning_ = true;
    algorithm_->start();
}

bool TimeAlgorithm::isRunning()
{
    return isRunning_;
}

