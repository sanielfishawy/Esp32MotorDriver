#include "ChargePump.h"


ChargePump::ChargePump(): 
    _timer(0)
{}

float ChargePump::getDuty(){
    if (! CP_REQUIRES_CHARGE_PUMP) return 0;

    _timer++;

    if (_timer % CP_TIME_BETWEEN_CHARGES_IN_PWM_CYCLES == 0){
        return -CP_CHARGE_TIME_IN_PWM_DUTY_CYCLE;
    }

    return 0.0;
}

void ChargePump::reset(){
    _timer = 0;
}