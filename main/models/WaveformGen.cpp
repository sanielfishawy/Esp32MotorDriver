#include "WaveformGen.h"

const char * WaveformGen::_logTag = "WaveformGen";

bool WaveformGen::_isSetup = false;
bool WaveformGen::_isStarted = false;

int   WaveformGen::_waveform = WG_SINE_WAVE;
float WaveformGen::_freqHz = 0.0;
float WaveformGen::_amplitudeFract = 0.0;

float WaveformGen::getDuty(float phaseOffsetRad){
    if(!_isSetup) {
        ESP_LOGE(_logTag, "getDuty(): WaveformGen must be setup before calling getDuty();");
        ESP_ERROR_CHECK(ESP_ERR_INVALID_STATE);
    }

    float phaseRad = PhaseGen::getPhaseRad() + phaseOffsetRad;
    return _getUnitValue(phaseRad) * _amplitudeFract;
};

float WaveformGen::_getUnitValue(float phaseRad){
    float sine = sin(phaseRad);
    if (_waveform == WG_SQUARE_WAVE) return sine > 0 ? 1 : -1;
    return sine;
};

void WaveformGen::setup(){
    if(_isSetup) return;
    PhaseGen::setup();
    _isSetup = true;
};

void WaveformGen::tearDown(){
    if(!_isSetup) return;
    if(_isStarted) stop();
    PhaseGen::tearDown();
    _isSetup = false;
};

void WaveformGen::start(){
    if(!_isSetup) return;
    if(_isStarted) return;
    PhaseGen::start();
    _isStarted = true;
};

void WaveformGen::stop(){
    if(!_isSetup) return;
    if(!_isStarted) return;
    PhaseGen::stop();
    _isStarted = false;
};

void WaveformGen::setWaveform(int waveform){
    _waveform = waveform;
}

int WaveformGen::getWaveform(){
    return(_waveform);
};

void WaveformGen::setFreqHz(float freqHz){
    if(!_isSetup) {
        ESP_LOGE(_logTag, "WG.setFreqHz(): WaveformGen must be setup before calling setFreqHz();");
        ESP_ERROR_CHECK(ESP_ERR_INVALID_STATE);
    }

    if (freqHz > WG_FREQ_MAX) freqHz = WG_FREQ_MAX;
    if (freqHz < WG_FREQ_MIN) freqHz = WG_FREQ_MIN;
    PhaseGen::setFreqHz(freqHz);
    _freqHz = freqHz;
};

float WaveformGen::getFreqHz(){
    return(_freqHz);
};

void WaveformGen::setAmplitudeFract(float amplitudeFract){
    if (amplitudeFract > WG_AMP_FRACT_MAX) amplitudeFract = WG_AMP_FRACT_MAX;
    if (amplitudeFract < WG_AMP_FRACT_MIN) amplitudeFract = WG_AMP_FRACT_MIN;
    _amplitudeFract = amplitudeFract;
};

float WaveformGen::getAmplitudeFract(){
    return(_amplitudeFract);
};
