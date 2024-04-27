#include "Integrator.h"

Integrator::Integrator():
    _integratorSize(PID_DEFAULT_INTEGRATOR_SIZE),
    _errors{0},
    _idx(0){
}

float Integrator::calculate(int error){
    _push(error);

    if (!_isFull) return 0;
    return _mean();
}

void Integrator::reset(){
    for (int i = 0; i < _integratorSize; i++){
        _errors[i] = 0;
    }
    _idx = 0;
    _isFull = false;
}

void Integrator::setIntegratorSize(int size){
    _integratorSize = size;
}

int Integrator::getIntegratorSize(){
    return _integratorSize;
}

void Integrator::_incrIdx(){
    if (_idx == _integratorSize - 1){
        _idx = 0;
        _isFull = true;
    } else {
        _idx++;
    }
}

void Integrator::_push(int error){
    _errors[_idx] = error;
    _incrIdx(); 
}

int Integrator::_sum(){
    int sum = 0;
    for (int i = 0; i < _integratorSize; i++){
        sum += _errors[i];
    }
    return sum;
}

float Integrator::_mean(){
    return (float) _sum() / _integratorSize;
}



