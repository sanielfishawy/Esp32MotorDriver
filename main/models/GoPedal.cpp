#include "GoPedal.h"

bool GoPedal::_isSetup = false;
adc_oneshot_unit_handle_t GoPedal::_adcHandle = nullptr;

void GoPedal::setup(){
    if(_isSetup) return;
    _setupPins();
    _setupAdc();
    _isSetup = true;
}

cJSON *GoPedal::getStatus(){
    cJSON *status = cJSON_CreateObject();
    if (!_isSetup){
        cJSON_AddBoolToObject(status, "ok", false);
        cJSON *error = cJSON_CreateObject();
        cJSON_AddStringToObject(error, "message", "not setup");
        cJSON_AddItemToObject(status, "error", error); 
        return(status);
    }
    if (!_channelsAgree()){
        cJSON_AddBoolToObject(status, "ok", false);
        cJSON *error = cJSON_CreateObject();
        cJSON_AddStringToObject(error, "message", "channels do not agree");
        cJSON_AddNumberToObject(error, "channelA", _getChanANormalized());
        cJSON_AddNumberToObject(error, "channelB", _getChanBNormalized());
        cJSON_AddItemToObject(status, "error", error);
        return(status);
    }
    cJSON_AddBoolToObject(status, "ok", true);
    return(status);
}

float GoPedal::getTorque(){
    if(!_isSetup) return(-1);
    if(!_channelsAgree()) return(-1);
    return _getChanANormalized();
}

int GoPedal::_getAdcRaw(adc_channel_t chan){
    if(!_isSetup) return(-1);
    int raw;
    ESP_ERROR_CHECK(adc_oneshot_read(_adcHandle, chan, &raw));
    return(raw);
}

float GoPedal::_getChanANormalized(){
    return _getAdcRaw(GP_ADC_CHANNEL_A) * GP_CHAN_A_NORM_FACTOR;
}

float GoPedal::_getChanBNormalized(){
    return _getAdcRaw(GP_ADC_CHANNEL_B) * GP_CHAN_B_NORM_FACTOR;
}

bool GoPedal::_channelsAgree(){
    return abs(_getChanANormalized() - _getChanBNormalized()) < GP_CHAN_AGREE_THRESHOLD;
}

void GoPedal::_setupPin(gpio_num_t pin){
    ESP_ERROR_CHECK(gpio_reset_pin(pin));
    ESP_ERROR_CHECK(gpio_intr_disable(pin));
    ESP_ERROR_CHECK(gpio_set_intr_type(pin, GPIO_INTR_DISABLE));
    ESP_ERROR_CHECK(gpio_set_pull_mode(pin, GPIO_FLOATING));
}

void GoPedal::_setupPins(){
    _setupPin(GP_ADC_GPIO_NUM_A);
    _setupPin(GP_ADC_GPIO_NUM_B);
}

void GoPedal::_setupAdc(){
    _setupAdcUnit();
    _setupAdcChannel();
}

void GoPedal::_setupAdcUnit(){
    adc_oneshot_unit_init_cfg_t _adcUnitConfig = {
        .unit_id = GP_ADC_UNIT,
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&_adcUnitConfig, &_adcHandle));
}

void GoPedal::_setupAdcChannel(){
    adc_oneshot_chan_cfg_t _adcChanCfg = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BIT_WIDTH,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(_adcHandle, STM_ADC_CHANNEL, &_adcChanCfg));
}