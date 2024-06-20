#include "Quadrature.h"

Quadrature::Quadrature(gpio_num_t aPinNum, gpio_num_t bPinNum):
    _aPinNum(aPinNum),
    _bPinNum(bPinNum),
    _count(0),
    _currentEvent({0, 0}),
    _previousEvent({0, 0}),
    _handleInterruptHandle(NULL)
{
    _setup();
}

void Quadrature::_setup(){
    _setupTask();
    _setupAPin();
    _setupBPin();
};

int64_t Quadrature::getCount(){
    return _count;
};

Quadrature::Event Quadrature::getCurrentEvent(){
    return _currentEvent;
};

Quadrature::Event Quadrature::getPreviousEvent(){
    return _previousEvent;
};

void Quadrature::_setupTask() {
    const BaseType_t core = 1;
    xTaskCreatePinnedToCore(
        Quadrature::_handleInterruptWrapper,  
        "QuadratureHandleInterrupt",
        10000,
        this,
        configMAX_PRIORITIES - 1,
        &_handleInterruptHandle,
        core
    );
}

void Quadrature::_handleInterruptWrapper(void *param) {
    static_cast<Quadrature*>(param)->_handleInterrupt();
}

TaskFunction_t Quadrature::_handleInterrupt(){
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 
        gpio_get_level(_bPinNum) ? _count++ : _count--;
        _previousEvent = _currentEvent;
        _currentEvent.count = _count;
        _currentEvent.timeUSec = esp_timer_get_time();
    }
};

void Quadrature::_setupAPin(){
    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE | ESP_INTR_FLAG_IRAM));
    ESP_ERROR_CHECK(gpio_reset_pin(_aPinNum));
    ESP_ERROR_CHECK(gpio_set_direction(_aPinNum, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_intr_enable(_aPinNum));
    ESP_ERROR_CHECK(gpio_set_intr_type(_aPinNum, GPIO_INTR_POSEDGE));
    ESP_ERROR_CHECK(gpio_isr_handler_add(_aPinNum, _gpioIsrHandlerWrapper, this));
};

void IRAM_ATTR Quadrature::_gpioIsrHandlerWrapper(void* arg) {
    auto* instance = static_cast<Quadrature*>(arg);
    if (instance) {
        instance->_gpioIsrHandler();
    }
}

void IRAM_ATTR Quadrature::_gpioIsrHandler(){
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(_handleInterruptHandle, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
};

void Quadrature::_setupBPin(){
    ESP_ERROR_CHECK(gpio_reset_pin(_bPinNum));
    ESP_ERROR_CHECK(gpio_set_direction(_bPinNum, GPIO_MODE_INPUT));
};