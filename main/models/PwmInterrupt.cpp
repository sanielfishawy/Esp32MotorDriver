// Deprecated. See PwmInterrupt.h for more information. Use PwmInterruptPin instead.
#include "PwmInterrupt.h"

#ifdef __cplusplus

#define TAG "PwmInterrupt"

bool PwmInterrupt::_isRunning = false;
bool PwmInterrupt::_isSetup = false;
gptimer_handle_t PwmInterrupt::_timer = NULL;

TaskHandle_t pwmInterruptHandlerHandle = NULL;

bool IRAM_ATTR PwmInterrupt::_onAlarm(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data) {
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(pwmInterruptHandlerHandle, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
    return true; 
}

void PwmInterrupt::pwmInterruptHandler(void *params) {
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait indefinitely for notification
        PwmPairs * pwmPairs = PwmPairs::getInstance();
        pwmPairs->handlePwmInterrupt();
    }
}

void PwmInterrupt::setup() {
    if(_isSetup) return;

    xTaskCreate(pwmInterruptHandler, "pwmInterruptHandler", 10000, NULL, 10, &pwmInterruptHandlerHandle);

    gptimer_handle_t gptimer = NULL;

    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_APB,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = APB_CLK_FREQ / PWM_INTR_MIN_CLOCK_DIVIDER, 
        .intr_priority = 0,
        .flags = {
            .intr_shared = true,
        }
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));

    gptimer_event_callbacks_t callback = {
        .on_alarm = _onAlarm,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &callback, nullptr));


    gptimer_alarm_config_t alarmConfig = {
        .alarm_count = APB_CLK_FREQ / PWM_INTR_MIN_CLOCK_DIVIDER / PWM_FREQ, // once per pwm period.
        .reload_count = 0,
        .flags = {
            .auto_reload_on_alarm = true,
        },
    };
    
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarmConfig));
    _timer = gptimer;
    _isSetup = true;
}

void PwmInterrupt::start() {
    if(!_timer || _isRunning) return;
    ESP_ERROR_CHECK(gptimer_enable(_timer));
    ESP_ERROR_CHECK(gptimer_start(_timer));
    _isRunning = true;
}

#endif // __cplusplus