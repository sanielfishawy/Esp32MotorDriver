#pragma once

#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "appConfig.h"
#include "PhaseGen.h"
#include "FastLog.h"

#ifdef __cplusplus

class WaveformGen{

    public:
        static void     setup();
        static void     tearDown();
        static void     start();
        static void     stop();
        
        static void    setWaveform(int waveform);
        static int     getWaveform();
        static void    setFreqHz(float freqHz);
        static float   getFreqHz();
        static void    setAmplitudeFract(float amplitudeFract);
        static float   getAmplitudeFract();

        static float   getDuty(float phaseOffsetRad);

    private:
        static const char * _logTag;

        static bool _isSetup;
        static bool _isStarted;

        static int   _waveform;
        static float _freqHz;
        static float _amplitudeFract;

        static float _getUnitValue(float phaseRad);
};

#endif // __cplusplus