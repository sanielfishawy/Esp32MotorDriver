#pragma once

#include "appConfig.h"
#include "Adc.h"
#include "WaveformGen.h"
#include "PwmPairs.h"
#include "PwmInterruptPin.h"

#ifdef __cplusplus

class VFD{
    public:
        static void setup();
        static void start();
        static void tearDown();
        static void stop();
        static void setFreqHz(float freqHz);
        static void setAmplitudeFract(float pPAmplitudeFract);
        static float getFreqHz();
        static float getAmplitudeFract();
        static void setActive();
        static void setFloat();
        static bool getIsActive();
        static bool getIsFloating();

    private:
        static bool _isSetup;
        static bool _isStarted;

};

#endif // __cplusplus