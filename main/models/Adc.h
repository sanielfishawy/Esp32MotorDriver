#include "soc/soc_caps.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/gpio.h"

#include "appConfig.h"

#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
class Adc{

    public:
        static void setup();
        static int readRaw(adc_channel_t chan);
        static float readVoltage(adc_channel_t chan);

    private:
        static bool _isSetup;
        static void _setupPins();
        static void _setupPin(gpio_num_t gpioNum);
        static void _setupAdc();
        static void _setupAdcUnit();
        static void _setupAdcChannel(adc_channel_t chan);
        static void _setupAdcChannels();
        static adc_oneshot_unit_handle_t _adcHandle;
        static adc_oneshot_unit_init_cfg_t _adcUnitConfig; 
        static adc_oneshot_chan_cfg_t _adcChanCfg;
};

#endif // __cplusplus

#endif  // ADC_H