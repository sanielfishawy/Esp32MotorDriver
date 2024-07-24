#include "Torque.h"

bool Torque::_isSetup = false;
adc_oneshot_unit_handle_t Torque::_adcHandle = nullptr;


void Torque::setup(){
    if(_isSetup) return;
    _setupPin();
    _setupAdc();
    _isSetup = true;
}

int Torque::getTorque(){
    if(!_isSetup) return(-1);
    int raw;
    ESP_ERROR_CHECK(adc_oneshot_read(_adcHandle, TORQUE_ADC_CHANNEL, &raw));
    return(raw);
}


void Torque::_setupPin(){
    ESP_ERROR_CHECK(gpio_reset_pin(TORQUE_ADC_GPIO_PIN));
    ESP_ERROR_CHECK(gpio_intr_disable(TORQUE_ADC_GPIO_PIN));
    ESP_ERROR_CHECK(gpio_set_intr_type(TORQUE_ADC_GPIO_PIN, GPIO_INTR_DISABLE));
    ESP_ERROR_CHECK(gpio_set_pull_mode(TORQUE_ADC_GPIO_PIN, GPIO_FLOATING));
}

void Torque::_setupAdc(){
    _setupAdcUnit();
    _setupAdcChannel();
}

void Torque::_setupAdcUnit(){
    adc_oneshot_unit_init_cfg_t _adcUnitConfig = {
        .unit_id = TORQUE_ADC_UNIT,
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&_adcUnitConfig, &_adcHandle));
}

void Torque::_setupAdcChannel(){
    adc_oneshot_chan_cfg_t _adcChanCfg = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BIT_WIDTH,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(_adcHandle, TORQUE_ADC_CHANNEL, &_adcChanCfg));
}


