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
    cJSON_AddNumberToObject(measurementJson, "startTime", _measurement.startTime);
    cJSON_AddNumberToObject(measurementJson, "endTime", _measurement.endTime);
    return measurementJson;
}

void Dynamic::setup(){
    if (_isSetup) return;
    VFD::setup();
    VFD::setFreqHz(1.0);
    VFD::setAmplitudeFract(0.0);
    VFD::start();
    _setupTimer();
    _isSetup = true;
}

void Dynamic::_setupTimer(){
    if (_timer != NULL) return;
    ESP_ERROR_CHECK(esp_timer_create(&_timerArgs, &_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(_timer, 1000 * 1000));
}

bool Dynamic::_isReady(){
    return _isSetup && _measurement.maxFreqHz != 0; 
}

bool Dynamic::_isGoingToMin(){
    return _measurement.startTime == 0;
}

bool Dynamic::_isNearMin(){
    return abs(_freqWithSlip() - _measurement.minFreqHz) < 0.05;
}

bool Dynamic::_isAtMin(){
    return VFD::getFreqHz() == _measurement.minFreqHz;
}

bool Dynamic::_isAboveMin(){
    return VFD::getFreqHz() > _measurement.minFreqHz;
}

bool Dynamic::_isBelowMin(){
    return VFD::getFreqHz() < _measurement.minFreqHz;
}

bool Dynamic::_isAtMax(){
    return VFD::getFreqHz() >= _measurement.maxFreqHz;
}

float Dynamic::_freqWithSlip(){
    return _rotorFreq() * ( 1 + _measurement.slipFract);
}

float Dynamic::_rotorFreq(){
    return VFD::getRotorElectricalEquivalentSpeedHz();
}

void Dynamic::_accelerate(){
    VFD::setFreqHz(_freqWithSlip());
    VFD::setAmplitudeFract(_measurement.amplitudeFract);
}

void Dynamic::_coast(){
    VFD::setFreqHz(_freqWithSlip());
    VFD::setAmplitudeFract(0.0);
}

void IRAM_ATTR Dynamic::_handleInterrupt(void *arg){
    ESP_LOGI(DYN_TAG, "_handleInterrupt");
    return;
    if (!_isReady()) return;

    if (_isGoingToMin()){
        _handleGoingToMin();
        return;
    }

    _handleAccelerating();
}

void Dynamic::_handleGoingToMin(){
    if (_isAtMin()){
        _measurement.startTime = esp_timer_get_time();
        _accelerate();
        return;
    }
    if (_isNearMin()){
        VFD::setFreqHz(_measurement.minFreqHz);
        VFD::setAmplitudeFract(_measurement.amplitudeFract);
        return;
    }
    if (_isAboveMin()){
        _coast();
        return;
    }
    if (_isBelowMin()){
        _accelerate();
        return;
    }
}

void Dynamic::_handleAccelerating(){
    if(_isAtMax()){
        _measurement.endTime = esp_timer_get_time();
        VFD::setFreqHz(_measurement.maxFreqHz);
        VFD::setAmplitudeFract(_measurement.amplitudeFract);
        return;
    }
    _accelerate();
}