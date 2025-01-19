#pragma once

#include "esp_log.h"
#include "hal/adc_types.h"
#include "soc/adc_channel.h"

#include "appConfig.h"

#ifdef __cplusplus

class Adc{
    public:
        static int readRaw(adc_channel_t channel);

    private:
        static void _setup();
        static bool _isSetup;
        static adc_oneshot_unit_handle_t _adc_handle;
        static void _setupAdc();
        static void _setupChannels();

};

#endif // __cplusplus