#include "GoPedal.h"

bool GoPedal::_isSetup = false;
bool GoPedal::_hadChannelMismatch = false;
float GoPedal::_currentTorque = 0;
esp_timer_handle_t GoPedal::_timer = NULL;
adc_oneshot_unit_handle_t GoPedal::_adcHandle = nullptr;

void GoPedal::setup(){
    if(_isSetup) return;
    _setupPins();
    _setupTimer();
    _isSetup = true;
}

float GoPedal::getTorque(){
    return _currentTorque;
}

void GoPedal::show(){
    int aRaw = _getAdcRaw(GP_ADC_CHANNEL_A);
    int bRaw = _getAdcRaw(GP_ADC_CHANNEL_B);
    float aNorm = _getChanANormalized();
    float bNorm = _getChanBNormalized();
    float torque = getTorque();
    ESP_LOGI(GP_TAG, "aRaw: %d, bRaw: %d, aNorm: %f, bNorm: %f, torque: %f", aRaw, bRaw, aNorm, bNorm, torque);
}

void GoPedal::_setupTimer(){
    if (_timer != NULL) return;
    ESP_ERROR_CHECK(esp_timer_create(&_timerArgs, &_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(_timer, 1000 * GP_UPDATE_PERIOD_MS));
}

void IRAM_ATTR GoPedal::_handleInterrupt(void *arg){
    if (!_isSetup) return;
    float torque = _getTorqueFromAdcs();
    if (torque < 0){
        _hadChannelMismatch = true;
        return;
    }
    _currentTorque = torque;
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
    if (_hadChannelMismatch){
        cJSON_AddBoolToObject(status, "ok", false);
        cJSON *error = cJSON_CreateObject();
        cJSON_AddStringToObject(error, "message", "channels did not agree");
        cJSON_AddItemToObject(status, "error", error);
        return(status);
    }
    cJSON_AddBoolToObject(status, "ok", true);
    return(status);
}

float GoPedal::_getTorqueFromAdcs(){
    if(!_isSetup) return(-1);
    float a = _getChanANormalized();
    float b = _getChanBNormalized();
    if(!_valuesAgree(a, b)) return(-1);
    return a;
}

int GoPedal::_getAdcRaw(adc_channel_t chan){
    if(!_isSetup) return(-1);
    return Adc::readRaw(chan);
}

float GoPedal::_getChanANormalized(){
    float r = ( _getAdcRaw(GP_ADC_CHANNEL_A) - GP_CHAN_A_MIN_RAW ) / GP_CHAN_A_RANGE;
    return GoPedal::_limitZeroToOne(r);
}

float GoPedal::_getChanBNormalized(){
    float r = ( _getAdcRaw(GP_ADC_CHANNEL_B) - GP_CHAN_B_MIN_RAW ) / GP_CHAN_B_RANGE;
    return _limitZeroToOne(r);
}

float GoPedal::_limitZeroToOne(float f){
    if (f < 0) return(0);
    if (f > 1) return(1);
    return(f);
}

bool GoPedal::_channelsAgree(){
    return _valuesAgree(_getChanANormalized(), _getChanBNormalized());
}

bool GoPedal::_valuesAgree(float a, float b){
    return abs(a - b) < GP_CHAN_AGREE_THRESHOLD;
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