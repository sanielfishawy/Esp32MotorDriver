#pragma once

#ifdef __cplusplus

class TunedParameters{

    typedef struct {
        float alpha;
        float beta;
        float gamma;
        float delta;
    } BilinearModelCoefficients;

    typedef struct {
        float startFreqHz;              // The freqHz to use when starting tbe motor below the lowCutoffRotorSpeed
        float startCutoffRotorSpeed;    // The speed below which motor is considered stopped and startFreq is used
        float linearCutoffRotorSpeed;   // The high limit where the slip is linearly interpolated
        float m;                        // Slope of the linear interpolation
        float b;                        // Y-intercept of the linear interpolation
        float highSlip;                 // The slip to use when rotorSpeed is above linearCutoffRotorSpeed
    } SlipCoefficients;

    public:
        static float getAmplitudeFractWithTorqueAndRotorSpeed(float torque, float rotorSpeed);
        static float getFreqHzForMaxTorqueWithRotorSpeed(float rotorSpeed);
        static float _getSlip(float rotorSpeed);
    
    private:
        static inline const BilinearModelCoefficients _blueMotorCoefficients = {
            .alpha = 0.176,
            .beta  = 0.475,
            .gamma = 0.016,
            .delta = 0.054,
        };

        static inline const BilinearModelCoefficients _ampCoeff = _blueMotorCoefficients;

        static inline const SlipCoefficients _blueMotorSlipCoefficients = {
            .startFreqHz = 3, 
            .startCutoffRotorSpeed = 1,
            .linearCutoffRotorSpeed = 16,
            .m = -0.022,
            .b = 0.62,
            .highSlip = 0.26,
        };  

        static inline const SlipCoefficients _slipCoeff = _blueMotorSlipCoefficients;
};



#endif // __cplusplus