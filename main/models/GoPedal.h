#pragma once

#include "soc/soc_caps.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "soc/adc_channel.h"
#include "cJSON.h"

#include "appConfig.h"

#ifdef __cplusplus

class GoPedal{

    public:
        static void  setup();
        static float getTorque();
        static cJSON *getStatus();
        static float _getChanANormalized();
        static float _getChanBNormalized();

    private:
        static bool _isSetup;

        static int   _getAdcRaw(adc_channel_t chan);
        static bool  _channelsAgree(); 
        static bool  _valuesAgree(float a, float b);
        static float _limitZeroToOne(float f);

        static void _setupPin(gpio_num_t pin);
        static void _setupPins();
        static void _setupAdc();
        static void _setupAdcUnit();
        static void _setupAdcChannels();
        static adc_oneshot_unit_handle_t _adcHandle;
};

#endif  // __cplusplus