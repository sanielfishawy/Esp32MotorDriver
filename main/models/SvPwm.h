#pragma once

#include <math.h>
#include "esp_log.h"
#include "cJSON.h"

#define SV_PWM_TAG "SvPwm"

#ifdef __cplusplus

typedef struct{
    float edge;
    float pw;
} SvPwmPulse;

typedef struct{
    SvPwmPulse aPulse;
    SvPwmPulse bPulse;
    SvPwmPulse cPulse;
} SvPwmPulses;

typedef struct{
    float theta;
    int   sector;
    float sectorTheta;
    float amp;
    float alpha;
    float beta;
    float zeroDegT;
    float sixtyDegT;
    float t0;
    float t1;
    float t2;
    float t3;
    float t4;
    float t5;
    float t6;
    SvPwmPulse aPulse;
    SvPwmPulse bPulse;
    SvPwmPulse cPulse;
    SvPwmPulses pulses;
} SvPwmAll;

class SvPwm{
    public:
        SvPwm(float theta, float amp);
        void aPulse(SvPwmPulse* pulse);
        void bPulse(SvPwmPulse* pulse);
        void cPulse(SvPwmPulse* pulse);
        void show();
        void pulses(SvPwmPulses* pulses);
        void getAll(SvPwmAll* all);
        static void fullRevolutionAsJson(int numPoints, cJSON* arr);

    private:
        static constexpr float SQRT3      = 1.73205080757f;
        static constexpr float PI_DIV_3   = 1.0471975512f;
        static constexpr float PI_2_DIV_3 = 2.09439510239f;
        static constexpr float PI_3_DIV_3 = 3.14159265359f;
        static constexpr float PI_4_DIV_3 = 4.18879020479f;
        static constexpr float PI_5_DIV_3 = 5.23598775598f;

        float _theta;
        float _sectorTheta;
        int   _sector;
        float _amp;
        float _alpha;
        float _beta;
        float _zeroDegT;
        float _sixtyDegT;

        float _t0;
        float _t1;
        float _t2;
        float _t3;
        float _t4;
        float _t5;
        float _t6;

        int   _getSector(float theta);
        void  _calcTs();
        void  _showPulse(const char *name, SvPwmPulse *pulse);
        void  _showPulses(SvPwmPulses *pulses);
};

#endif // __cplusplus
