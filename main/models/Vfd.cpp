#include "Vfd.h"

bool VFD::_isSetup = false;
bool VFD::_isStarted = false;

void VFD::setup(){
    if(_isSetup) return;
    PhaseGen::setup();
    PhaseGen::setFreqHz(60);
    PwmPairs::setAmplitudeFract(1);

    PwmPairs::setup();
    
    _isSetup = true;
}

void VFD::start(){
    if(_isStarted) return;

    PhaseGen::start();
    PwmPairs::startPwm();

    _isStarted = true;
}

void VFD::setFreqHz(float freqHz){
    PhaseGen::setFreqHz(freqHz);
}

void VFD::setAmplitudeFract(float amplitudeFract){
    PwmPairs::setAmplitudeFract(amplitudeFract);
}

float VFD::getFreqHz(){
    return PhaseGen::getFreqHz();
}

float VFD::getAmplitudeFract(){
    return PwmPairs::getAmplitudeFract();
}

void VFD::setActive(){
    PwmPairs::setActive();
}

void VFD::setFloat(){
    PwmPairs::setFloat();
}

bool VFD::getIsActive(){
    return PwmPairs::getIsActive();
}
bool VFD::getIsFloating(){
    return PwmPairs::getIsFloating();
}