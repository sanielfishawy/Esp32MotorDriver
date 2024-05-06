#include "PwmPair.h"

PwmPair::PwmPair(   gpio_num_t highGpioNum,
                    ledc_channel_t highChannelNum,
                    gpio_num_t lowGpioNum,
                    ledc_channel_t lowChannelNum,
                    adc_channel_t adcChan,
                    float phaseOffsetRad,
                    bool enableLog): 
    _pid(),
    _phaseOffsetRad(phaseOffsetRad),
    _highGpioNum(highGpioNum),
    _highChannelNum(highChannelNum),
    _lowGpioNum(lowGpioNum),
    _lowChannelNum(lowChannelNum),
    _highPin(highGpioNum, highChannelNum),  
    _lowPin(lowGpioNum, lowChannelNum),
    _adcChan(adcChan),
    _enableLog(enableLog),
    _chargePumpTimer(0)
{}

void PwmPair::startPwm(){
    _highPin.startPwm();
    _lowPin.startPwm();
}


void PwmPair::setDuty(float duty){
    if (duty <= -1) duty = -0.95;
    if (duty >= 1) duty = 0.95;

    if (duty > 0){
        _highPin.setDuty(duty);
        _lowPin.setDuty(0);
    } else {
        _highPin.setDuty(0);
        _lowPin.setDuty(-duty);
    }

    if (duty < -0.08) _resetChargePump();
}

void PwmPair::handlePwmInterrupt(){
    if (_handleChargePump()) return;
    if (OpenLoopClosedLoop::isClosedLoop()){
        _handleClosedLoop();
    } else {
        _handleOpenLoop();
    }
}

void PwmPair::_resetChargePump(){
    _chargePumpTimer = 0;
}

bool PwmPair::_handleChargePump(){
    _chargePumpTimer++;

    if(_chargePumpTimer % 10 == 0){
        setDuty(-0.05);
        return true;
    }
    return false;
}

void PwmPair::_handleClosedLoop(){
    int setPoint = WaveformGen::getPoint(_phaseOffsetRad);
    int actPoint = readRawAdc();
    float dty = _pid.calculate(setPoint, actPoint);
    if(_enableLog) FastLog::set(setPoint, actPoint, dty);
    setDuty(dty);
}

void PwmPair::_handleOpenLoop(){
    static bool toggle = true;
    float phaseRad = PhaseGen::getPhaseRad();

    if(sin(phaseRad) > 0){
        if (toggle){
            setDuty(0.95);
        } else {
            setDuty(-0.05);
        }
    } else {
        if (toggle){
            setDuty(-0.95);
        } else {
            setDuty(0.05);
        }
    }
    toggle = !toggle;
}


int PwmPair::readRawAdc(){
    return Adc::readRaw(_adcChan);
}