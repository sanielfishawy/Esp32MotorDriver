#pragma once

#ifdef __cplusplus

#include <cstdlib>
#include "esp_timer.h"
#include "esp_err.h"
#include "esp_log.h"
#include "cJSON.h"

#include "Vfd.h"

class Dynamic{

    typedef struct{
        float minFreqHz;
        float maxFreqHz;
        float slipFract;
        float amplitudeFract;
        uint64_t startTime;
        uint64_t endTime;
    } Measurement;

    public:
        static void setup();
        static void setupMeasurement(Measurement measurement);
        static esp_err_t setupMeasurementFromJson(cJSON *measurementJson);
        static Measurement getMeasurement();
        static cJSON *getMeasurementJson();
        
    private:
        static Measurement _measurement;
        static bool  _isSetup;
        static bool  _isReady();
        static bool  _isGoingToMin();
        static bool  _isNearMin();
        static bool  _isAtMin();
        static bool  _isAboveMin();
        static bool  _isBelowMin();
        static bool  _isAtMax();
        static float _freqWithSlip();
        static float _rotorFreq();
        static void  _accelerate();
        static void  _coast();
        static void  _handleGoingToMin();
        static void  _handleAccelerating();

        static void IRAM_ATTR           _handleInterrupt(void * arg);
        static esp_timer_create_args_t  _timerArgs;
        static esp_timer_handle_t       _timer;
        static void                     _setupTimer();
};

#endif  // __cplusplus