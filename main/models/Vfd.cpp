#include "Vfd.h"

bool VFD::_isSetup = false;
bool VFD::_isStarted = false;

void VFD::setup(){
    if(_isSetup) return;
    WaveformGen::setup();
    WaveformGen::setFreqHz(50);
    WaveformGen::setAmplitudeFract(0.5);
    WaveformGen::setWaveform(WG_SINE_WAVE);

    PwmPairs::setup();
    
    _isSetup = true;
}

void VFD::start(){
    if(_isStarted) return;

    WaveformGen::start();
    PwmPairs::startPwm();

    _isStarted = true;
}

void VFD::setFreqHz(float freqHz){
    WaveformGen::setFreqHz(freqHz);
}

void VFD::setAmplitudeFract(float amplitudeFract){
    WaveformGen::setAmplitudeFract(amplitudeFract);
}

float VFD::getFreqHz(){
    return WaveformGen::getFreqHz();
}

float VFD::getAmplitudeFract(){
    return WaveformGen::getAmplitudeFract();
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