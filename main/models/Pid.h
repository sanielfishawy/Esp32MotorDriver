#pragma once

#include "appConfig.h"
#include "Integrator.h"
#include "Derivator.h"

#ifdef __cplusplus

class PID{

    public:
        PID();
        float calculate(int setPoint, int actPoint);
        void setKp(float kP);
        void setKi(float kI);
        void setKd(float kD);
        float getKp();
        float getKi();
        float getKd();

    private:
        Integrator * _integrator;
        Derivator * _derivator;
        float _kP;
        float _kI;
        float _kD;

        float _clamp(float value);
};

#endif // __cplusplus