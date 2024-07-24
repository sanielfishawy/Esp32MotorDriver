#pragma once

#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/gpio.h"

#include "appConfig.h"

#ifdef __cplusplus

class Torque{
    public:
        static void setup();
        static int  getTorque();

    private:
        static bool _isSetup;
        static void _setupPin();
        static void _setupAdc();
        static void _setupAdcUnit();
        static void _setupAdcChannel();
        static adc_oneshot_unit_handle_t _adcHandle;

};

#endif  // __cplusplus