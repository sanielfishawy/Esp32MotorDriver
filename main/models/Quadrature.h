#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <array>

#include "appConfig.h"

#ifdef __cplusplus

class Quadrature{
    public:
        Quadrature(gpio_num_t aPinNum, gpio_num_t bPinNum);
        struct Event {
            int64_t count;
            int64_t timeUSec;
        };
        int64_t getCount();
        Event   getCurrentEvent();
        Event   getPreviousEvent();

    private:
        gpio_num_t  _aPinNum;
        gpio_num_t  _bPinNum;
        int64_t     _count;
        Event _currentEvent;
        Event _previousEvent;

        void _setup();
        void _setupTask();
        void _setupAPin();
        void _setupBPin();

        TaskHandle_t _handleInterruptHandle;
        static void _handleInterruptWrapper(void *param);
        TaskFunction_t _handleInterrupt();
        static void IRAM_ATTR _gpioIsrHandlerWrapper(void* arg);
        void _gpioIsrHandler();
};

#endif