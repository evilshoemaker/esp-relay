#ifndef RelayAlgorithm_h
#define RelayAlgorithm_h

#include <Arduino.h>

class RelayAlgorithm
{
public:
    RelayAlgorithm(uint8_t relay1Pin, uint8_t relay2Pin, uint8_t relay3Pin);

    void init();
    void tick();
    void start();
    void stop();
    bool isRunning();

private:
    enum AlgorithmState {
        IDLE_STATE = 0,
        STEP_1_STATE,
        STEP_2_SLEEP_STATE,
        STEP_3_STATE,
        STEP_4_SLEEP_STATE,
        STEP_5_STATE,
        STEP_6_SLEEP_STATE, 
        STEP_7_STATE,
        STOPED_STATE
        
    } currentState_ = IDLE_STATE;

    uint8_t relay1Pin_ = 0;
    uint8_t relay2Pin_ = 0;
    uint8_t relay3Pin_ = 0;

    uint32_t lastUpdateTime_ = 0;
};

#endif

