#include "DCVoltage.h"

bool DCVoltage::_isSetup = false;

float DCVoltage::readVoltage() {
    _setup();
    int raw = Adc::readRaw(DCV_ADC_CHANNEL);
    return (float) 100.0 * raw / DCV_RAW_FOR_100_V;
}

void DCVoltage::_setup() {
    if (_isSetup) return;
    _setupGpio();
    ESP_LOGI(DCV_TAG, "setup");
    _isSetup = true;
}

void DCVoltage::_setupGpio() {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << DCV_GPIO_NUM),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}
