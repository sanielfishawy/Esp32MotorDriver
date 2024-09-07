#include "TorqueControl.h"

bool  TorqueControl::_isSetup = false;
float TorqueControl::_torque = 0;
bool  TorqueControl::_useGoPedal = true;

esp_timer_create_args_t TorqueControl::_timerArgs = {
    .callback = &_handleInterrupt,
    .arg = NULL,
    .dispatch_method = ESP_TIMER_TASK,
    .name = "torqueControlTimer",
    .skip_unhandled_events = true,
};

esp_timer_handle_t TorqueControl::_timer = NULL;

void TorqueControl::_setupTimer(){
    if (_timer != NULL) return;
    ESP_ERROR_CHECK(esp_timer_create(&_timerArgs, &_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(_timer, 1000 * TC_VFD_UPDATE_PERIOD_MS));
}

void TorqueControl::setup(){
    ESP_LOGI(TC_TAG, "Motor running under TorqueControl");
    if(_isSetup) return;
    GoPedal::setup();
    VFD::setup();
    VFD::start();
    _setupTimer();
    _isSetup = true;
} 

void TorqueControl::setUseGoPedal(bool useGoPedal){
    ESP_LOGI(TC_TAG, "Setting useGoPedal to %d", useGoPedal);
    if (useGoPedal == _useGoPedal) return;
    if (!useGoPedal) _torque = 0;
    _useGoPedal = useGoPedal;
}

bool TorqueControl::getUseGoPedal(){
    return _useGoPedal;
}

void TorqueControl::_setMotorTorque(){
    if(!_isSetup){
        ESP_LOGE(TC_TAG, "setup() must be called before setTorque()");
        return;
    }

    float t = _torque;
    if (t < 0) t = 0;
    if (t > 1) t = 1;

    float rotorFreq = _rotorFreq();

    float newFreqHz = TunedParameters::getFreqHzForMaxTorqueWithRotorFreq(rotorFreq);
    float newAmp = TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(t, rotorFreq);
    VFD::setFreqHz(newFreqHz);
    VFD::setAmplitudeFract(newAmp);
}

void TorqueControl::setTorque(float torque){
    _torque = torque;
}

float TorqueControl::getTorque(){
    return _torque;
}

float TorqueControl::_rotorFreq(){
    return VFD::getRotorElectricalEquivalentSpeedHz();
}

void IRAM_ATTR TorqueControl::_handleInterrupt(void *arg){
    if (!_isSetup) return;
    else if (getUseGoPedal()) setTorque(GoPedal::getTorque());
    _setMotorTorque();
}