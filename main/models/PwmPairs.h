#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "appConfig.h"
#include "PwmPair.h"
#include "TestOutputPin.h"

#ifndef PWM_PAIRS_H
#define PWM_PAIRS_H

#define PWM_PAIRS_TAG "PwmPairs: "

#ifdef __cplusplus

class PwmPairs{
    public:
        static PwmPairs* getInstance();

        void startPwm();
        void handlePwmInterrupt();

    protected:
        PwmPairs();

    private:
        static PwmPairs* _instance;
        static SemaphoreHandle_t _mutex;
        static void initializeMutex();

        void _toggleTestOutputPin();

        bool _isRunning;
        PwmPair *_pairA;
        PwmPair *_pairB;
        PwmPair *_pairC;
};

#endif  // __cplusplus

#endif  // PWM_PAIRS_H