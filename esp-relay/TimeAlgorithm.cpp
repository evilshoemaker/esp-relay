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
    if (!algorithm_->isRunning())
    {
        algorithmTimeEnd_ = sleepMs;
        algorithmTimeStart_ = millis();
        algorithm_->start();
    }
}

bool TimeAlgorithm::isRunning()
{
    return algorithm_->isRunning();
}

