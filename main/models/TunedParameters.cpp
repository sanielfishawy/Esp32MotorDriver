#include "TunedParameters.h"

// See pythonTuning project for how this model was fit.
float TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(float torque, float rotorFreq){
    float amp = _getAmpParabolicModel(torque, rotorFreq);
    if (amp > 1) return 1;
    return amp;
}

float TunedParameters::_getAmpBilinearModel(float torque, float rotorFreq){
    if (rotorFreq < _bilinearModelAmpCoeff.lowCutoffRotorFreq) return 0.75 * torque;
    return  _bilinearModelAmpCoeff.alpha + 
            _bilinearModelAmpCoeff.beta * torque + 
            _bilinearModelAmpCoeff.gamma * rotorFreq +
            _bilinearModelAmpCoeff.delta * torque * rotorFreq;
}

float TunedParameters::_getAmpLinearModel(float torque, float rotorFreq){
    if (rotorFreq < 3) return 0.75 * torque;
    return 0.171 * rotorFreq * torque;
}

float TunedParameters::_getAmpParabolicModel(float torque, float rotorFreq){
    if (rotorFreq < _parabolicModelAmpCoeff.lowCutoffRotorFreq) return 0.75 * torque;
    float k =   _parabolicModelAmpCoeff.a * rotorFreq * rotorFreq + 
                _parabolicModelAmpCoeff.b * rotorFreq + 
                _parabolicModelAmpCoeff.c;
    return k * torque;
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