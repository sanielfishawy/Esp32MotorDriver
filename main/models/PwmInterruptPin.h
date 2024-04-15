#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "appConfig.h"
#include "PwmPin.h"
#include "PwmPairs.h"

#ifndef PWM_INTERRUPT_PIN_H
#define PWM_INTERRUPT_PIN_H

#ifdef __cplusplus
class PwmInterruptPin{

    public:
        static void startPwm();
        static void setup();

    private:
        static bool _isStarted;
        static bool _isSetup;
        static PwmPin *_pwmPin;
        static TaskHandle_t _handleInteruptHandle;


        static void _setupIntrGpioIn();
        static void _setupTask();
        static void IRAM_ATTR _gpio_isr_handler(void* arg);
        static void _handleInterrupt(void *params);

};
#endif // __cplusplus

#endif  // PWM_INTERRUPT_PIN_H