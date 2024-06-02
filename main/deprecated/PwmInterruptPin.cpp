#include "PwmInterruptPin.h"

// Private attributes
PwmPin * PwmInterruptPin::_pwmPin = nullptr;
TaskHandle_t PwmInterruptPin::_handleInteruptHandle = NULL;
bool PwmInterruptPin::_isStarted = false;
bool PwmInterruptPin::_isSetup = false;

// Public methods
void PwmInterruptPin::setup(){
    if (_isSetup) return;
    _pwmPin = new PwmPin(PWM_INTR_PIN_OUT_GPIO_NUM, PWM_INTR_PIN_CHANNEL_NUM); 
    _setupTask();
    _setupIntrGpioIn();
    _isSetup = true;
};

void PwmInterruptPin::startPwm(){
    if (_isStarted) return;
    if (_pwmPin == nullptr) return;
    _pwmPin->startPwm();
    _pwmPin->setDuty(0.5);
    _isStarted = true;
}


// Private methods

void PwmInterruptPin::_setupTask(){
    const BaseType_t core = 0;
    xTaskCreatePinnedToCore(
        _handleInterrupt,
        "PwmInterruptPinHandleInterrupt",
        10000,
        nullptr,
        configMAX_PRIORITIES - 1,
        &_handleInteruptHandle,
        core
    );
}

void PwmInterruptPin::_setupIntrGpioIn(){
    // ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE | ESP_INTR_FLAG_LEVEL6 | ESP_INTR_FLAG_IRAM));
    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE | ESP_INTR_FLAG_IRAM));
    ESP_ERROR_CHECK(gpio_reset_pin(PWM_INTR_PIN_IN_GPIO_NUM));
    ESP_ERROR_CHECK(gpio_set_direction(PWM_INTR_PIN_IN_GPIO_NUM, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_intr_enable(PWM_INTR_PIN_IN_GPIO_NUM));
    ESP_ERROR_CHECK(gpio_set_intr_type(PWM_INTR_PIN_IN_GPIO_NUM, GPIO_INTR_POSEDGE));
    ESP_ERROR_CHECK(gpio_isr_handler_add(PWM_INTR_PIN_IN_GPIO_NUM, _gpio_isr_handler, nullptr));
};


void IRAM_ATTR PwmInterruptPin::_gpio_isr_handler(void* arg){
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(_handleInteruptHandle, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
};

void PwmInterruptPin::_handleInterrupt(void *params){
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // Wait indefinitely for notification
        PwmPairs::handleInterrupt();
    }
};

