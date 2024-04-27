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
        static void setPPAmplitudeFract(float pPAmplitudeFract);
        static void setDcOffsetFract(float dcOffsetFract);

    private:
        static bool _isSetup;
        static bool _isStarted;

};

#endif // __cplusplus