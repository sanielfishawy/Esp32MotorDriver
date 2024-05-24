#pragma once

#include "math.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_task_wdt.h"
#include "esp_timer.h"

#include "appConfig.h"
#include "PwmPair.h"
#include "PwmInterruptPin.h"
#include "FastLog.h"
#include "WaveformGen.h"

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
        static void setActive();
        static void setFloat();
        static bool getIsActive();
        static bool getIsFloating();

    private:
        static bool _isSetup;
        static bool _isStarted;
        static PwmPair _pairA;
        static PwmPair _pairB;
        static PwmPair _pairC;
        static float _phaseOffsetRadB;
        static float _phaseOffsetRadC;
};

#endif  // __cplusplus
