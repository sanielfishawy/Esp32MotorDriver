#include "FastLog.h"

float FastLog::_duty = 0;

void FastLog::set(float duty){
    _duty = duty;
}

void FastLog::log(){
    ESP_LOGI("FastLog", "Duty: %f", _duty);
}