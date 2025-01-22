#pragma once

#include "soc/soc_caps.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "soc/adc_channel.h"
#include "cJSON.h"
#include "esp_timer.h"

#include "appConfig.h"
#include "Adc.h"

#ifdef __cplusplus

class GoPedal{

    public:
        static void  setup();
        static cJSON *getStatus();
        static float _getChanANormalized();
        static float _getChanBNormalized();
        static float getTorque();
        static void show();

    private:
        static bool _isSetup;

        static float _getTorqueFromAdcs();
        static int   _getAdcRaw(adc_channel_t chan);
        static bool  _channelsAgree(); 
        static bool  _valuesAgree(float a, float b);
        static float _limitZeroToOne(float f);

        static float _currentTorque;
        static bool  _hadChannelMismatch;
        static void _setupPin(gpio_num_t pin);
        static void _setupPins();
        static void _setupAdc();
        static void _setupAdcUnit();
        static void _setupAdcChannels();
        static adc_oneshot_unit_handle_t _adcHandle;

        static esp_timer_handle_t       _timer;
        static void IRAM_ATTR           _handleInterrupt(void * arg);
        static void                     _setupTimer();
        
        static inline const esp_timer_create_args_t  _timerArgs = {
            .callback = &_handleInterrupt,
            .arg = NULL,
            .dispatch_method = ESP_TIMER_TASK,
            .name = "goPedalTimer",
            .skip_unhandled_events = true,
        };
};

#endif  // __cplusplus