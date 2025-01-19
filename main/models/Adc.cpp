#include "Adc.h"

bool Adc::_isSetup = false;
adc_oneshot_unit_handle_t Adc::_adc_handle = NULL;


void Adc::_setup() {
    if (_isSetup) return;
    _setupAdc();
    _setupChannels();
    _isSetup = true;
    ESP_LOGI(ADC_TAG, "is setup");
}

int Adc::readRaw(adc_channel_t channel){
    _setup();
    int rawValue = -1;
    ESP_ERROR_CHECK(adc_oneshot_read(_adc_handle, channel, &rawValue));
    return rawValue;
}

// I set up only 1 adc to be safe
void Adc::_setupAdc(){
    adc_oneshot_unit_init_cfg_t adcConfig = {
        .unit_id = ADC_UNIT_1,
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&adcConfig, &_adc_handle));
}

// I set up only the channels we use. One of the ADC channels is used by usb boot loader.
void Adc::_setupChannels(){
    adc_oneshot_chan_cfg_t chanConfig = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(_adc_handle, (adc_channel_t) ADC1_GPIO1_CHANNEL, &chanConfig));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(_adc_handle, (adc_channel_t) ADC1_GPIO2_CHANNEL, &chanConfig));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(_adc_handle, (adc_channel_t) ADC1_GPIO3_CHANNEL, &chanConfig));
}

