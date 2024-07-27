#include "Dynamic.h"

bool  Dynamic::_isSetup = false;

Dynamic::Measurement Dynamic::_measurement = {
    .minFreqHz = 0.0,
    .maxFreqHz = 0.0,
    .slipFract = 0.0,
    .amplitudeFract = 0.0,
    .startTime = 0,
    .endTime = 0,
};

esp_timer_create_args_t Dynamic::_timerArgs = {
    .callback = &_handleInterrupt,
    .arg = NULL,
    .dispatch_method = ESP_TIMER_TASK,
    .name = "dynamic",
    .skip_unhandled_events = true,
};

esp_timer_handle_t Dynamic::_timer = NULL;

void Dynamic::setupMeasurement(Measurement measurement){
    _measurement = measurement;
}

esp_err_t Dynamic::setupMeasurementFromJson(cJSON *measurement){
    if (measurement == NULL || !cJSON_IsObject(measurement)){
        ESP_LOGE(DYN_TAG, "setupMeasurementFromJson: measurement is not an object");
        return ESP_ERR_INVALID_ARG;
    } 
    cJSON *minFreqHz = cJSON_GetObjectItemCaseSensitive(measurement, "minFreqHz");
    if (minFreqHz == NULL || !cJSON_IsNumber(minFreqHz)){
        ESP_LOGE(DYN_TAG, "setupMeasurementFromJson: minFreqHz is not a number");
        return ESP_ERR_INVALID_ARG;
    }
    cJSON *maxFreqHz = cJSON_GetObjectItemCaseSensitive(measurement, "maxFreqHz");
    if (maxFreqHz == NULL || !cJSON_IsNumber(maxFreqHz)){
        ESP_LOGE(DYN_TAG, "setupMeasurementFromJson: maxFreqHz is not a number");
        return ESP_ERR_INVALID_ARG;
    }
    cJSON *slipFract = cJSON_GetObjectItemCaseSensitive(measurement, "slipFract");
    if (slipFract == NULL || !cJSON_IsNumber(slipFract)){
        ESP_LOGE(DYN_TAG, "setupMeasurementFromJson: slipFract is not a number");
        return ESP_ERR_INVALID_ARG;
    }
    cJSON *amplitudeFract = cJSON_GetObjectItemCaseSensitive(measurement, "amplitudeFract");
    if (amplitudeFract == NULL || !cJSON_IsNumber(amplitudeFract)){
        ESP_LOGE(DYN_TAG, "setupMeasurementFromJson: amplitudeFract is not a number");
        return ESP_ERR_INVALID_ARG;
    }
    _measurement.minFreqHz = minFreqHz->valuedouble;
    _measurement.maxFreqHz = maxFreqHz->valuedouble;
    _measurement.slipFract = slipFract->valuedouble;
    _measurement.amplitudeFract = amplitudeFract->valuedouble;
    _measurement.startTime = 0;
    _measurement.endTime = 0;
    ESP_LOGI(DYN_TAG, "setupMeasurementFromJson: minFreqHz: %f, maxFreqHz: %f, slipFract: %f, amplitudeFract: %f", _measurement.minFreqHz, _measurement.maxFreqHz, _measurement.slipFract, _measurement.amplitudeFract);
    return ESP_OK;
}

Dynamic::Measurement Dynamic::getMeasurement(){
    return _measurement;
}
    
cJSON *Dynamic::getMeasurementJson(){
    cJSON *measurementJson = cJSON_CreateObject();
    cJSON_AddNumberToObject(measurementJson, "minFreqHz", _measurement.minFreqHz);
    cJSON_AddNumberToObject(measurementJson, "maxFreqHz", _measurement.maxFreqHz);
    cJSON_AddNumberToObject(measurementJson, "slipFract", _measurement.slipFract);
    cJSON_AddNumberToObject(measurementJson, "amplitudeFract", _measurement.amplitudeFract);
    cJSON_AddNumberToObject(measurementJson, "startTime", (float) _measurement.startTime);
    cJSON_AddNumberToObject(measurementJson, "endTime", (float) _measurement.endTime);
    return measurementJson;
}

void Dynamic::setup(){
    if (_isSetup) return;
    VFD::setup();
    VFD::start();
    _setupTimer();
    _isSetup = true;
}

void Dynamic::_setupTimer(){
    if (_timer != NULL) return;
    ESP_ERROR_CHECK(esp_timer_create(&_timerArgs, &_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(_timer, 1000 * DYN_VFD_UPDATE_PERIOD_MS));
}

bool Dynamic::_isReady(){
    return _isSetup && _measurement.maxFreqHz != 0; 
}

bool Dynamic::_isGoingToMin(){
    return _measurement.startTime == 0;
}

bool Dynamic::_isNearMin(){
    return abs(VFD::getFreqHz() - _measurement.minFreqHz) < 0.8;
}

bool Dynamic::_isAtMin(){
    bool atMin = VFD::getFreqHz() == _measurement.minFreqHz && VFD::getSlipFract() < 0.02;
    // ESP_LOGI(DYN_TAG, "isAtMin: %d,  f: %f, s: %f, ", atMin, VFD::getFreqHz(), VFD::getSlipFract());
    return atMin;
}

bool Dynamic::_isAboveMin(){
    return VFD::getFreqHz() > _measurement.minFreqHz;
}

bool Dynamic::_isBelowMin(){
    return VFD::getFreqHz() < _measurement.minFreqHz;
}

bool Dynamic::_isAtMax(){
    return _rotorFreq() >= _measurement.maxFreqHz;
}

bool Dynamic::_isStopped(){
    return _rotorFreq() < 0.5;
}

bool Dynamic::_isDone(){
    return _measurement.endTime != 0;
}

bool Dynamic::_isNotAbleToAccelerate(){
    return esp_timer_get_time() - _measurement.startTime > 1000000 * DYN_NOT_ABLE_TO_ACCEL_THRESHOLD_SEC;
}

float Dynamic::_freqWithSlip(float slipFract){
    return _rotorFreq() / ( 1 - slipFract);
}

float Dynamic::_freqWithSlip(){
    return _freqWithSlip(_measurement.slipFract);
}

float Dynamic::_rotorFreq(){
    return VFD::getRotorElectricalEquivalentSpeedHz();
}

float Dynamic::_rotorSlipFract(){
    return VFD::getSlipFract();
}

void Dynamic::_accelerate(){
    float fws = _freqWithSlip();
    VFD::setFreqHz(fws);
    VFD::setAmplitudeFract(_measurement.amplitudeFract);
    // ESP_LOGI(DYN_TAG, "accelerate: freq: %f amp: %f", fws, _measurement.amplitudeFract);
}

bool Dynamic::_accelerateFromStopped(){
    if (_isStopped()){
        VFD::setFreqHz(DYN_START_FREQ_HZ);
        VFD::setAmplitudeFract(DYN_START_AMP_FRACT);
        // ESP_LOGI(DYN_TAG, "accelerateFromStopped:");
        return true;
    }
    return false;
}

void Dynamic::_accelerateToMin(){
    if (_accelerateFromStopped()) return;
    VFD::setFreqHz(_freqWithSlip(DYN_ACCEL_TO_MIN_SLIP_FRACT));
    VFD::setAmplitudeFract(DYN_ACCEL_TO_MIN_AMP_FRACT);
    // ESP_LOGI(DYN_TAG, "accelerateToMin:");
}   

void Dynamic::_coast(){
    VFD::setFreqHz(_freqWithSlip(DYN_ACCEL_TO_MIN_SLIP_FRACT));
    VFD::setAmplitudeFract(0.0);
}

void IRAM_ATTR Dynamic::_handleInterrupt(void *arg){
    // ESP_LOGI(DYN_TAG, "_handleInterrupt");
    if (!_isReady() || _isDone()){
        // ESP_LOGI(DYN_TAG, "not ready: %d or done: %d", !_isReady(), _isDone());
        _coast();
        return;
    } 

    if (_isGoingToMin()){
        _handleGoingToMin();
        return;
    }

    _handleAccelerating();
}

void Dynamic::_handleGoingToMin(){
    // ESP_LOGI(DYN_TAG, "_handleGoingToMin");
    if (_isAtMin()){
        // ESP_LOGI(DYN_TAG, "at min");
        _measurement.startTime = esp_timer_get_time();
        _accelerate();
        return;
    }
    if (_isNearMin()){
        // ESP_LOGI(DYN_TAG, "near min");
        VFD::setFreqHz(_measurement.minFreqHz);
        VFD::setAmplitudeFract(DYN_ACCEL_TO_MIN_AMP_FRACT);
        return;
    }
    if (_isAboveMin()){
        // ESP_LOGI(DYN_TAG, "above min");
        _coast();
        return;
    }
    if (_isBelowMin()){
        // ESP_LOGI(DYN_TAG, "below min");
        _accelerateToMin();
        return;
    }
}

void Dynamic::_handleAccelerating(){
    // ESP_LOGI(DYN_TAG, "_handleAccelerating");
    if(_isAtMax()){
        // ESP_LOGI(DYN_TAG, "at max");
        if (_measurement.endTime == 0) _measurement.endTime = esp_timer_get_time();
        _coast();
        return;
    }
    
    if(_isNotAbleToAccelerate()){
        // ESP_LOGI(DYN_TAG, "not able to accelerate");
        _measurement.endTime = -1;
        _coast();
        return;
    }

    _accelerate();
}