#include "RelayAlgorithm.h"

const uint32_t SLEEP1_MS = 900;
const uint32_t SLEEP2_MS = 900;
const uint32_t SLEEP3_MS = 800;

RelayAlgorithm::RelayAlgorithm(uint8_t relay1Pin, uint8_t relay2Pin, uint8_t relay3Pin) :
    relay1Pin_(relay1Pin),
    relay2Pin_(relay2Pin),
    relay3Pin_(relay3Pin)
{
    
}

void RelayAlgorithm::init()
{
    pinMode(relay1Pin_, OUTPUT);
    pinMode(relay2Pin_, OUTPUT);
    pinMode(relay3Pin_, OUTPUT);

    digitalWrite(relay1Pin_, HIGH);
    digitalWrite(relay2Pin_, HIGH);
    digitalWrite(relay3Pin_, HIGH);
}

void RelayAlgorithm::tick()
{
    if (currentState_ == STOPED_STATE)
    {
        digitalWrite(relay1Pin_, HIGH);
        digitalWrite(relay2Pin_, HIGH);
        digitalWrite(relay3Pin_, HIGH);

        currentState_ = IDLE_STATE;
    }
    else if (currentState_ == STEP_1_STATE)
    {
        digitalWrite(relay1Pin_, LOW);
        digitalWrite(relay2Pin_, HIGH);
        digitalWrite(relay3Pin_, HIGH);
        
        currentState_ = STEP_2_SLEEP_STATE;
        lastUpdateTime_ = millis();
    }
    else if (currentState_ == STEP_2_SLEEP_STATE)
    {
        if ((millis() - lastUpdateTime_) > SLEEP1_MS)
        {
            currentState_ = STEP_3_STATE;
        }
    }
    else if (currentState_ == STEP_3_STATE)
    {
        digitalWrite(relay2Pin_, LOW);
        
        currentState_ = STEP_4_SLEEP_STATE;
        lastUpdateTime_ = millis();
    }
    else if (currentState_ == STEP_4_SLEEP_STATE)
    {
        if ((millis() - lastUpdateTime_) > SLEEP2_MS)
        {
            currentState_ = STEP_5_STATE;
        }
    }
    else if (currentState_ == STEP_5_STATE)
    {
        digitalWrite(relay2Pin_, HIGH);
        digitalWrite(relay3Pin_, LOW);
        
        currentState_ = STEP_6_SLEEP_STATE;
        lastUpdateTime_ = millis();
    }
    else if (currentState_ == STEP_6_SLEEP_STATE)
    {
        if ((millis() - lastUpdateTime_) > SLEEP3_MS)
        {
            currentState_ = STEP_7_STATE;
        }
    }
}

void RelayAlgorithm::start()
{
    currentState_ = STEP_1_STATE;
}

void RelayAlgorithm::stop()
{
    currentState_ = STOPED_STATE;
}

bool RelayAlgorithm::isRunning()
{
    return currentState_ == IDLE_STATE;
}

