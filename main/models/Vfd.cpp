#include "Vfd.h"

bool VFD::_isSetup = false;
bool VFD::_isStarted = false;
float VFD::_maxFreqHz = VFD_DEFAULT_MAX_FREQ_HZ;

void VFD::setup(){
    if(_isSetup) return;
    PhaseGen::setup();
    PhaseGen::setFreqHz(3);
    PwmPairs::setAmplitudeFract(0);

    PwmPairs::setup();
    RotorSpeed::setup();
    
    _isSetup = true;
}

void VFD::start(){
    if(_isStarted) return;

    PhaseGen::start();
    PwmPairs::startPwm();

    _isStarted = true;
}

void VFD::setFreqHz(float freqHz){
    float limitedFreqHz = freqHz > _maxFreqHz ? _maxFreqHz : freqHz;
    PhaseGen::setFreqHz(limitedFreqHz);
}

void VFD::setMaxFreqHz(float freqHz){
    _maxFreqHz = freqHz;
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

float VFD::getRotorSpeedHz(){
    return RotorSpeed::getSpeedHz();
}   

float VFD::getRotorElectricalEquivalentSpeedHz(){
    return RotorSpeed::getElectricalEquivalentSpeedHz();
}

float VFD::getSlipFract(){
    return getSlipHz() / getFreqHz();
}

float VFD::getSlipHz(){
    return  getFreqHz() - RotorSpeed::getElectricalEquivalentSpeedHz();
}