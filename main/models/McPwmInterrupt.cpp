#include "McPwmInterrupt.h"

TaskHandle_t McPwmInterrupt::_handleInteruptHandle = NULL;
bool McPwmInterrupt::_isSetup = false;
std::function<void()> McPwmInterrupt::_callback = nullptr;

void McPwmInterrupt::setup(mcpwm_timer_handle_t timer, std::function<void()> callback){
    if (_isSetup) return;
    _callback = callback;
    _setupTask();
    _setupTimerInterrupt(timer);
    _isSetup = true;
};

void McPwmInterrupt::_setupTask(){
    const BaseType_t core = 0;
    xTaskCreatePinnedToCore(
        _handleInterrupt,
        "McPwmInterruptTask",
        10000,
        nullptr,
        configMAX_PRIORITIES - 1,
        &_handleInteruptHandle,
        core
    );
}

void McPwmInterrupt::_setupTimerInterrupt(mcpwm_timer_handle_t timer){
    const mcpwm_timer_event_callbacks_t cbs = {
        .on_full = nullptr,
        .on_empty = _interruptHandler,
        .on_stop = nullptr,
    };
    mcpwm_timer_register_event_callbacks(timer, &cbs, nullptr);
};


bool IRAM_ATTR McPwmInterrupt::_interruptHandler(mcpwm_timer_handle_t timer, const mcpwm_timer_event_data_t *edata, void *user_ctx){
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(_handleInteruptHandle, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
    return true;
};

void McPwmInterrupt::_handleInterrupt(void *params){
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait indefinitely for notification
        if (_callback){
            _callback();
        } else {
            ESP_LOGE(MC_PWM_INTERRUPT_TAG, "No callback set");
            ESP_ERROR_CHECK(ESP_FAIL);
        }
    }
};

