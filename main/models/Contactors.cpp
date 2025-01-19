#include "Contactors.h"

bool Contactors::_isSetup = false; 

void Contactors::setup() {
    if (_isSetup) return;
    ESP_LOGI(CT_TAG, "setup");
    setupGpio(CT_DC_ON_GPIO_NUM);
    setupGpio(CT_DC_CHG_GPIO_NUM);
    setupGpio(CT_DC_DIS_CHG_GPIO_NUM);
        dcOff();
    dcChgOff();
    dcDisChgOn();
    _isSetup = true;
}

void Contactors::setupGpio(gpio_num_t gpioNum) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << gpioNum),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void Contactors::dcOn() {
    gpio_set_level(CT_DC_ON_GPIO_NUM, 1);
}

void Contactors::dcOff() {
    gpio_set_level(CT_DC_ON_GPIO_NUM, 0);
}

void Contactors::dcChgOn() {
    gpio_set_level(CT_DC_CHG_GPIO_NUM, 1);
}   

void Contactors::dcChgOff() {
    gpio_set_level(CT_DC_CHG_GPIO_NUM, 0);
}   

void Contactors::dcDisChgOn() {
    gpio_set_level(CT_DC_DIS_CHG_GPIO_NUM, 1);
}

void Contactors::dcDisChgOff() {
    gpio_set_level(CT_DC_DIS_CHG_GPIO_NUM, 0);
}   




