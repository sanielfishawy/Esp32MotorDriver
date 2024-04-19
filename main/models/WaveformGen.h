#pragma once

#include "esp_err.h"
#include "esp_log.h"

#include "appConfig.h"
#include "PhaseGen.h"

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
        static void    setPPAmplitudeFract(float pPAmplitudeFract);
        static float   getPPAmplitudeFract();
        static void    setDcOffsetFract(float dcOffsetFract);
        static float   getDcOffsetFract();

        static int     getPoint(float phaseOffsetRad);

    private:
        static const char * _logTag;

        static bool _isSetup;
        static bool _isStarted;

        static int   _waveform;
        static float _freqHz;
        static float _pPAmplitudeFract;
        static float _dcOffsetFract;
};

#endif // __cplusplus