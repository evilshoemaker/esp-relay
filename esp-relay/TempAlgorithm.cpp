#include "TempAlgorithm.h"

TempAlgorithm::TempAlgorithm(RelayAlgorithm *algorithm, DS18B20 *DS18B20Sensor) :
    algorithm_(algorithm),
    DS18B20Sensor_(DS18B20Sensor)
{
    
}

void TempAlgorithm::tick()
{
    if (!isRunning_)
        return;

    if (currentState_ == HEAT_STATE)
    {
        if (DS18B20Sensor_->temperature() < tempMax_ && 
                !algorithm_->isRunning())
        {
            algorithm_->start();
        }
        else if (DS18B20Sensor_->temperature() >= tempMax_) 
        {
            currentState_ = COOl_DOWN_STATE;
        }
    }
    else if (currentState_ == COOl_DOWN_STATE)
    {
        if (DS18B20Sensor_->temperature() >= tempMin_ && 
                algorithm_->isRunning())
        {
            algorithm_->stop();
        }
        else if (DS18B20Sensor_->temperature() < tempMin_) 
        {
            currentState_ = HEAT_STATE;
        }
    }
}

void TempAlgorithm::start(int tempMin, int tempMax)
{
    tempMin_ = tempMin;
    tempMax_ = tempMax;
    
    isRunning_ = true;

    if (DS18B20Sensor_->temperature() < tempMax)
    {
        currentState_ = HEAT_STATE;
    }
    else
    {
        currentState_ = COOl_DOWN_STATE;
    }
}

void TempAlgorithm::stop()
{
    isRunning_ = false;
    algorithm_->stop();
}

bool TempAlgorithm::isRunning()
{
    return isRunning_;//algorithm_->isRunning();
}

