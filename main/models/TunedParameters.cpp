#include "TunedParameters.h"

// See pythonTuning project for how this model was fit.
float TunedParameters::getAmplitudeFractWithTorqueAndRotorSpeed(float torque, float rotorSpeed){
    float amp = _ampCoeff.alpha + 
                _ampCoeff.beta * torque + 
                _ampCoeff.gamma * rotorSpeed +
                _ampCoeff.delta * torque * rotorSpeed;
    if (amp > 1) return 1;
    return amp;
}

float TunedParameters::_getSlip(float rotorSpeed){
    if (rotorSpeed <= _slipCoeff.startCutoffRotorSpeed) return 0;
    else if (rotorSpeed <= _slipCoeff.linearCutoffRotorSpeed) return _slipCoeff.m * rotorSpeed + _slipCoeff.b;
    else return _slipCoeff.highSlip;
}

float TunedParameters::getFreqHzForMaxTorqueWithRotorSpeed(float rotorSpeed){
    float slip = _getSlip(rotorSpeed);
    if (slip == 0) return _slipCoeff.startFreqHz;
    return rotorSpeed + _getSlip(rotorSpeed) * rotorSpeed;
}