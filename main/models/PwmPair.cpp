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
    _enableLog(enableLog)
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
}

void PwmPair::handlePwmInterrupt(){
    static long long chargePump = 0;
    chargePump ++;
    if(chargePump % 50 == 0){
        setDuty(-0.05);
        return;
    }

    int setPoint = WaveformGen::getPoint(_phaseOffsetRad);
    int actPoint = readRawAdc();
    float dty = _pid.calculate(setPoint, actPoint);
    if(_enableLog) FastLog::set(setPoint, actPoint, dty);
    setDuty(dty);
}


int PwmPair::readRawAdc(){
    return Adc::readRaw(_adcChan);
}