#include "RotorSpeed.h"

bool RotorSpeed::_isSetup = false;
Quadrature* RotorSpeed::_quadrature = nullptr;

void RotorSpeed::setup(){
    if (_isSetup) return;
    _quadrature = new Quadrature(RS_QUAD_A_GPIO_NUM, RS_QUAD_B_GPIO_NUM);
    _isSetup = true;
}


float RotorSpeed::getSpeedHz(){
    if (!_isSetup){
        ESP_LOGE(RS_TAG, "RotorSpeed not setup");
    }


    Quadrature::Event currentEvent = _quadrature->getCurrentEvent();
    Quadrature::Event previousEvent = _quadrature->getPreviousEvent();

    if (isSpeedZero(currentEvent)){
        return (float) 0.0;
    }

    int64_t deltaTimeUsec = currentEvent.timeUSec - previousEvent.timeUSec;
    if (deltaTimeUsec == 0) return (float) 0.0;
    float deltaTimeSec = (float) deltaTimeUsec / 1000000.0;

    int64_t deltaCount = currentEvent.count - previousEvent.count;
    float deltaRev = (float) deltaCount / RS_QAUD_TICKS_PER_REV;
    return (float) deltaRev / deltaTimeSec;
}

bool RotorSpeed::isSpeedZero(Quadrature::Event currentEvent){
    return esp_timer_get_time() - currentEvent.timeUSec > RS_MAX_TIME_BETWEEN_TICKS_USEC;
}

float RotorSpeed::getElectricalEquivalentSpeedHz(){
    return MOTOR_POLES * getSpeedHz() / 2.0;
}