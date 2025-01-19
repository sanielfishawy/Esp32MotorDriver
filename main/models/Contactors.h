#pragma once

#include "esp_log.h"
#include "driver/gpio.h"

#include "appConfig.h"

#ifdef __cplusplus

class Contactors {
    public:
        static void setup();

    private:
        static bool _isSetup;
        static void setupGpio(gpio_num_t gpioNum);
        static void dcOn();
        static void dcOff();
        static void dcChgOn();
        static void dcChgOff();
        static void dcDisChgOn();
        static void dcDisChgOff();

};

#endif // __cplusplus