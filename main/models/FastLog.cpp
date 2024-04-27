#include "FastLog.h"

int FastLog::_setPoint = 0;
int FastLog::_actPoint = 0;
float FastLog::_duty = 0;

void FastLog::set(int setPoint, int actPoint, float duty){
    _setPoint = setPoint;
    _actPoint = actPoint;
    _duty = duty;
}

void FastLog::log(){
    ESP_LOGI("FastLog", "Set: %d, Act: %d, Duty: %f", _setPoint, _actPoint, _duty);
}