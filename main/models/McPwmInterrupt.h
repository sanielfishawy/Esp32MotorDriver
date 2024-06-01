#pragma once

#include <functional>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/mcpwm_prelude.h"    
#include "esp_attr.h"
#include "esp_log.h"

#include "appConfig.h"
#include "PwmPairs.h"

#define MC_PWM_INTERRUPT_TAG "McPwmInterrupt"

#ifdef __cplusplus
class McPwmInterrupt{

    public:
        static void setup(mcpwm_timer_handle_t timer, std::function<void()> callback);

    private:
        static bool _isSetup;
        static std::function<void()> _callback;
        static TaskHandle_t _handleInteruptHandle;


        static void _setupTimerInterrupt(mcpwm_timer_handle_t timer);
        static bool IRAM_ATTR _interruptHandler(mcpwm_timer_handle_t timer, const mcpwm_timer_event_data_t *edata, void *user_ctx);
        static void _handleInterrupt(void *params);
        static void _setupTask();

};
#endif // __cplusplus
