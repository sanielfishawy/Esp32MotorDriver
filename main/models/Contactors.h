#pragma once

#include "esp_log.h"
#include "driver/gpio.h"
#include "cJSON.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string>

#include "appConfig.h"
#include "DCVoltage.h"

#ifdef __cplusplus

class Contactors {
    public:
        enum class State {
            ON,
            CHARGING,
            DISCHARGING,
            OFF,
            FAULT,
        };
        static void powerUp();
        static void powerDown();
        static State getState();
        static std::string getStateString();
        static cJSON *getStatusJson();

    private:
        static void _setup();
        static bool _isSetup;
        static void _setupGpio(gpio_num_t gpioNum);
        static void _dcOn();
        static void _dcOff();
        static void _dcChgOn();
        static void _dcChgOff();
        static void _dcDisChgOn();
        static void _dcDisChgOff();
        static bool _isDcOn();
        static bool _isDcChgOn();
        static bool _isDcDisChgOn();
        static bool _isOn();
        static bool _isCharging();
        static bool _isDischarging();
        static bool _isOff();
        static bool _isFault();
};

#endif // __cplusplus