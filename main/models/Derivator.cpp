#include "Derivator.h"


Derivator::Derivator(): _priorError(0) {
}

float Derivator::calculate(int error){
    float r = (error - _priorError) / PWM_PERIOD_SEC;
    _priorError = error;
    return r;
}

void Derivator::reset(){
    _priorError = 0;
}

