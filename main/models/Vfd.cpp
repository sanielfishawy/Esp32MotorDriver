#include "Vfd.h"

bool VFD::_isSetup = false;
bool VFD::_isStarted = false;

void VFD::setup(){
    if(_isSetup) return;
    Adc::setup();

    WaveformGen::setup();
    WaveformGen::setFreqHz(10);
    WaveformGen::setPPAmplitudeFract(0.5);
    WaveformGen::setWaveform(WG_SQUARE_WAVE);

    PwmPairs::setup();
    
    _isSetup = true;
};

void VFD::start(){
    if(_isStarted) return;

    WaveformGen::start();
    PwmPairs::startPwm();

    _isStarted = true;
};