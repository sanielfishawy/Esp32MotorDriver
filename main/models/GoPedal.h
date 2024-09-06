#pragma once

#include "soc/soc_caps.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "cJSON.h"

#include "appConfig.h"

#ifdef __cplusplus

class GoPedal{

    public:
        static void  setup();
        static float getTorque();
        static cJSON *getStatus();

    private:
        static bool _isSetup;

        static int   _getAdcRaw(adc_channel_t chan);
        static float _getChanANormalized();
        static float _getChanBNormalized();
        static bool  _channelsAgree(); 

        static void _setupPin(gpio_num_t pin);
        static void _setupPins();
        static void _setupAdc();
        static void _setupAdcUnit();
        static void _setupAdcChannel();
        static adc_oneshot_unit_handle_t _adcHandle;
};

#endif  // __cplusplus