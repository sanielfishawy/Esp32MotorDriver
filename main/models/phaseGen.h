#include <stdio.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "appConfig.h"
#include "PhaseGenTimer.h"

#ifndef PHASEGEN_H
#define PHASEGEN_H

#ifdef __cplusplus

class PhaseGen{

    public:
        static void setup();
        static void tearDown();
        static void start();
        static void stop();
        static void setPeriodSec(float periodSec);
        static void setFreqHz(float freqHz);
        static float getPhaseRad();
        static int getPeriodTicks();
        static uint64_t getTimerTick();
        static float getPeriodSec();
        static float getFreqHz();

    private:
        static const char *_logTag;
        static bool _isStarted;
        static bool _isSetup;
        static int _periodTicks;
        static int _previousPeriodTicks;

        static void _setTimerTick(uint64_t tick);
        static uint64_t _getTimerTick();
        
        static void _checkAndAdjustForPeriodChange();

        static void _setPeriodTicks(int ticks);

        static int _phaseTickNum();
        static int _previousPhaseTickNum();

        static float _phaseFraction();
        static float _previousPhaseFraction();

        static uint64_t _timerTicksForPeriodChange();

};

#endif // __cplusplus

#endif // PHASEGEN_H