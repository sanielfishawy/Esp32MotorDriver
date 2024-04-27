#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "appConfig.h"
#include "PwmPair.h"
#include "PwmInterruptPin.h"

#ifndef PWM_PAIRS_H
#define PWM_PAIRS_H

#define PWM_PAIRS_TAG "PwmPairs: "

#ifdef __cplusplus

class PwmPairs{
    public:
        static void setup();
        static void startPwm();
        static void handlePwmInterrupt();
        static void setPairADuty(float duty);
        static void setPairBDuty(float duty);
        static void setPairCDuty(float duty);
        static int  readRawAdcA();
        static int  readRawAdcB();
        static int  readRawAdcC();

    private:
        static bool _isSetup;
        static bool _isStarted;
        static PwmPair _pairA;
        static PwmPair _pairB;
        static PwmPair _pairC;
};

#endif  // __cplusplus

#endif  // PWM_PAIRS_H