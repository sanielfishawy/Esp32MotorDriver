#pragma once

#include "appConfig.h"

#ifdef __cplusplus

class Integrator{

    public:
        Integrator(); 
        float calculate(int point);
        void reset();
        void setIntegratorSize(int size);
        int getIntegratorSize();

    private:
        int _integratorSize;
        int _errors[10];
        int _idx = 0;
        bool _isFull = false;

        void _push(int error);
        void _incrIdx();
        int _sum();
        float _mean();
};

#endif // __cplusplus