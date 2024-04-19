#include "WaveformGen.h"

const char * WaveformGen::_logTag = "WaveformGen";

bool WaveformGen::_isSetup = false;
bool WaveformGen::_isStarted = false;

int   WaveformGen::_waveform = WG_SINE_WAVE;
float WaveformGen::_freqHz = 0.0;
float WaveformGen::_pPAmplitudeFract = 0.0;
float WaveformGen::_dcOffsetFract = 0.5;

int WaveformGen::getPoint(float phaseOffsetRad){
    if(!_isSetup) {
        ESP_LOGE(_logTag, "getPoint(): WaveformGen must be setup before calling getPoint();");
        ESP_ERROR_CHECK(ESP_ERR_INVALID_STATE);
    }

    float phaseRad = PhaseGen::getPhaseRad() + phaseOffsetRad;
    float ppGain = static_cast<float>( WG_MAX_ADC_VALUE ) * _pPAmplitudeFract;    
    float gain = ppGain / 2;
    float offset = static_cast<float>( WG_MAX_ADC_VALUE ) * _dcOffsetFract;
    float unitValue = sin(phaseRad);

    ESP_LOGI(_logTag, "getPoint(): phaseRad = %f, phaseFract = %f, gain = %f, offset = %f, unitValue = %f", phaseRad, phaseRad / 2 / M_PI, gain, offset, unitValue);

    return (int) ( ( gain * unitValue) + offset );
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
        ESP_LOGE(_logTag, "getPoint(): WaveformGen must be setup before calling setFreqHz();");
        ESP_ERROR_CHECK(ESP_ERR_INVALID_STATE);
    }

    PhaseGen::setFreqHz(freqHz);
    _freqHz = freqHz;
};

float WaveformGen::getFreqHz(){
    return(_freqHz);
};

void WaveformGen::setPPAmplitudeFract(float pPAmplitudeFract){
    _pPAmplitudeFract = pPAmplitudeFract;
};

float WaveformGen::getPPAmplitudeFract(){
    return(_pPAmplitudeFract);
};

void WaveformGen::setDcOffsetFract(float dcOffsetFract){
    _dcOffsetFract = dcOffsetFract;
};

float WaveformGen::getDcOffsetFract(){
    return(_dcOffsetFract);
};
