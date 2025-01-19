#pragma once

#include "esp_log.h"
#include "driver/gpio.h"

#include "appConfig.h"
#include "adc.h"

#ifdef __cplusplus

class DCVoltage {
    public:
        static float readVoltage();

    private:
        static bool _isSetup;
        static void _setup();
        static void _setupGpio();

};

#endif // __cplusplus