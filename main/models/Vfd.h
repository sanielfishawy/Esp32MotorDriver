#pragma once

#include "appConfig.h"
#include "Adc.h"
#include "PwmPairs.h"
#include "RotorSpeed.h"

#ifdef __cplusplus

class VFD{

    public:
        static void setup();
        static void start();
        static void tearDown();
        static void stop();
        static void setFreqHz(float freqHz);
        static void setMaxFreqHz(float freqHz);
        static void setAmplitudeFract(float pPAmplitudeFract);
        static float getFreqHz();
        static float getAmplitudeFract();
        static void setActive();
        static void setFloat();
        static bool getIsActive();
        static bool getIsFloating();
        static float getRotorSpeedHz();
        static float getRotorElectricalEquivalentSpeedHz();
        static float getSlipHz();
        static float getSlipFract();

    private:
        static bool _isSetup;
        static bool _isStarted;
        static float _maxFreqHz;

};

#endif // __cplusplus