#include "TimeAlgorithm.h"

TimeAlgorithm::TimeAlgorithm(RelayAlgorithm *algorithm) :
    algorithm_(algorithm)
{
    
}

void TimeAlgorithm::tick()
{
    if (isRunning_ && algorithm_->isRunning())
    {
        if ((millis() - algorithmTimeStart_) > algorithmTimeEnd_)
        {
            algorithm_->stop();
            isRunning_ = false;
        }
    }
}

void TimeAlgorithm::start(uint32_t sleepMs)
{
    if (!algorithm_->isRunning())
    {
        isRunning_ = true;
        algorithmTimeEnd_ = sleepMs;
        algorithmTimeStart_ = millis();
        algorithm_->start();
    }
}

void TimeAlgorithm::stop()
{
    isRunning_ = false;
    algorithm_->stop();
}

bool TimeAlgorithm::isRunning()
{
    return isRunning_;
}
