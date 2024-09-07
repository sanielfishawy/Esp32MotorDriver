#include "TunedParameters.h"

// See pythonTuning project for how this model was fit.
float TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(float torque, float rotorFreq){
    float amp = _ampCoeff.alpha + 
                _ampCoeff.beta * torque + 
                _ampCoeff.gamma * rotorFreq +
                _ampCoeff.delta * torque * rotorFreq;
    if (amp > 1) return 1;
    return amp;
}

float TunedParameters::_getSlip(float rotorFreq){
    if (rotorFreq <= _slipCoeff.startCutoffRotorFreq) return 0;
    else if (rotorFreq <= _slipCoeff.linearCutoffRotorFreq) return _slipCoeff.m * rotorFreq + _slipCoeff.b;
    else return _slipCoeff.highSlip;
}

float TunedParameters::getFreqHzForMaxTorqueWithRotorFreq(float rotorFreq){
    float slip = _getSlip(rotorFreq);
    if (slip == 0) return _slipCoeff.startFreqHz;
    return rotorFreq + _getSlip(rotorFreq) * rotorFreq;
}