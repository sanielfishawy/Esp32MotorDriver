#include <stdio.h>
#include <math.h>
#include "appConfig.h"
#include "PhaseGenTimer.h"

#ifndef PHASEGEN_H
#define PHASEGEN_H

#ifdef __cplusplus

class PhaseGen{

    public:
        static void setup();
        static void start();
        static void setPeriodSec(float periodSec);
        static void setFreqHz(float freqHz);
        static float phaseRadians();

    private:
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