#pragma once

#include "math.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_task_wdt.h"
#include "esp_timer.h"

#include "appConfig.h"
#include "McPwmPair.h"
#include "McPwmInterrupt.h"
#include "FastLog.h"
#include "PhaseGen.h"
#include "SvPwm.h"

#define PWM_PAIRS_TAG "PwmPairs: "

#ifdef __cplusplus

class PwmPairs{
    public:
        static void setup();
        static void startPwm();
        static void pairAPulse(float lead, float pulseWidth);
        static void pairBPulse(float lead, float pulseWidth);
        static void pairCPulse(float lead, float pulseWidth);
        static void setActive();
        static void setFloat();
        static bool getIsActive();
        static bool getIsFloating();
        static void setAmplitudeFract(float amplitudeFract);
        static float getAmplitudeFract();
        static void handleInterrupt();

    private:
        static bool _isSetup;
        static void _syncPairs();
        static void _setupInterrupt();
        static bool _isStarted;
        static McPwmPair _pairA;
        static McPwmPair _pairB;
        static McPwmPair _pairC;
        static float _amplitudeFract;
};

#endif  // __cplusplus
