#include "PwmPairs.h"

#ifdef __cplusplus

// Public attributes
PwmPairs* PwmPairs::_instance = nullptr;
SemaphoreHandle_t PwmPairs::_mutex = nullptr;

void PwmPairs::initializeMutex() {
    static bool isMutexInitialized = false;
    if (!isMutexInitialized) {
        _mutex = xSemaphoreCreateMutex();
        isMutexInitialized = true;
    }
}


// Public methods
PwmPairs* PwmPairs::getInstance() {
    if (_mutex == nullptr) {
        initializeMutex(); // Ensure the mutex is initialized before use
    }

    if (_instance == nullptr) {
        xSemaphoreTake(_mutex, portMAX_DELAY);
        if (_instance == nullptr) {
            _instance = new PwmPairs(); // Safely create the singleton instance
        }
        xSemaphoreGive(_mutex);
    }
    return _instance;
}

void PwmPairs::startPwm(){
    if (!_isRunning){
        _pairA->startPwm();
        _pairB->startPwm();
        _pairC->startPwm();
        _isRunning = true;
    }
}

void PwmPairs::handlePwmInterrupt(){
    _toggleTestOutputPin();
    _pairA->handlePwmInterrupt();
    _pairB->handlePwmInterrupt();
    _pairC->handlePwmInterrupt();
}

void PwmPairs::_toggleTestOutputPin(){
    TestOutputPin *tp = TestOutputPin::getInstance();
    static bool toggle = false;
    if(toggle) tp->setLevel(1);
    else tp->setLevel(0);
    toggle = !toggle;
}

// Protected methods
PwmPairs::PwmPairs(){
    _pairA = new PwmPair(PWM_A_HIGH_GPIO_NUM, PWM_A_HIGH_CHANNEL_NUM, PWM_A_LOW_GPIO_NUM, PWM_A_LOW_CHANNEL_NUM);
    _pairB = new PwmPair(PWM_B_HIGH_GPIO_NUM, PWM_B_HIGH_CHANNEL_NUM, PWM_B_LOW_GPIO_NUM, PWM_B_LOW_CHANNEL_NUM);
    _pairC = new PwmPair(PWM_C_HIGH_GPIO_NUM, PWM_C_HIGH_CHANNEL_NUM, PWM_C_LOW_GPIO_NUM, PWM_C_LOW_CHANNEL_NUM);
    _isRunning = false;
}

#endif  // __cplusplus