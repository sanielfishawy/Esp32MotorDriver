#include "Adc.h"

bool Adc::_isSetup = false;
adc_oneshot_unit_handle_t Adc::_adcHandle = nullptr;
adc_oneshot_unit_init_cfg_t Adc::_adcUnitConfig = {};
adc_oneshot_chan_cfg_t Adc::_adcChanCfg = {};

void Adc::setup(){
    if(_isSetup) return;
    _setupPins();
    _setupAdc();
    _isSetup = true;
}

int Adc::readRaw(adc_channel_t chan){
    if(!_isSetup) return(-1);

    int raw;
    ESP_ERROR_CHECK(adc_oneshot_read(_adcHandle, chan, &raw));
    return(raw);
}

float Adc::readVoltage(adc_channel_t chan){
    if(!_isSetup) return(-1);
    float m = 0.000777;
    float b = 0.0849;

    float raw = (float) readRaw(chan);
    // float v = ((float) raw * ADC_MAX_VOLTAGE_FLOAT) / (float) ADC_MAX_VOLTAGE_BINARY;
    float v = (m * raw) + b;
    return(v);
}   

void Adc::_setupPins(){
    _setupPin(ADC_CHANNEL_O_GPIO_NUM);
    _setupPin(ADC_CHANNEL_1_GPIO_NUM);
    _setupPin(ADC_CHANNEL_2_GPIO_NUM);
}

void Adc::_setupPin(gpio_num_t gpioNum){
    ESP_ERROR_CHECK(gpio_reset_pin(gpioNum));
    ESP_ERROR_CHECK(gpio_intr_disable(gpioNum));
    ESP_ERROR_CHECK(gpio_set_intr_type(gpioNum, GPIO_INTR_DISABLE));
    ESP_ERROR_CHECK(gpio_set_pull_mode(gpioNum, GPIO_FLOATING));
}

void Adc::_setupAdc(){
    _setupAdcUnit();
    _setupAdcChannels();
}

void Adc::_setupAdcUnit(){
    adc_oneshot_unit_init_cfg_t _adcUnitConfig = {
        .unit_id = ADC_UNIT_1,
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&_adcUnitConfig, &_adcHandle));
}

void Adc::_setupAdcChannel(adc_channel_t chan){
    adc_oneshot_chan_cfg_t _adcChanCfg = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BIT_WIDTH,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(_adcHandle, chan, &_adcChanCfg));
}

void Adc::_setupAdcChannels(){
    _setupAdcChannel(ADC_CHANNEL_0);
    _setupAdcChannel(ADC_CHANNEL_1);
    _setupAdcChannel(ADC_CHANNEL_2);
}


