#pragma once

#ifdef __cplusplus

class TunedParameters{

    typedef struct {
        float lowCutoffRotorFreq;
        float alpha;
        float beta;
        float gamma;
        float delta;
    } BilinearModelCoefficients;

    typedef struct{
        float lowCutoffRotorFreq;
        float a;
        float b;
        float c;
    } ParabolicModelCoefficients;

    typedef struct {
        float startFreqHz;              // The freqHz to use when starting tbe motor below the lowCutoffRotorSpeed
        float startCutoffRotorFreq;     // The speed below which motor is considered stopped and startFreq is used
        float linearCutoffRotorFreq;    // The high limit where the slip is linearly interpolated
        float m;                        // Slope of the linear interpolation
        float b;                        // Y-intercept of the linear interpolation
        float highSlip;                 // The slip to use when rotorFreq is above linearCutoffRotorFreq
    } SlipCoefficients;

    public:
        static float getAmplitudeFractWithTorqueAndRotorFreq(float torque, float rotorFreq);
        static float getFreqHzForMaxTorqueWithRotorFreq(float rotorFreq);
    
    private:
        static float _getSlip(float rotorFreq);
        static float _getAmpBilinearModel(float torque, float rotorFreq);
        static float _getAmpLinearModel(float torque, float rotorFreq);
        static float _getAmpParabolicModel(float torque, float rotorFreq);

        static inline const BilinearModelCoefficients _biLinearBlueMotorCoefficients = {
            .lowCutoffRotorFreq = 3,
            .alpha = 0.176,
            .beta  = 0.475,
            .gamma = 0.016,
            .delta = 0.054,
        };

        static inline const BilinearModelCoefficients _bilinearModelAmpCoeff = _biLinearBlueMotorCoefficients;

        static inline const ParabolicModelCoefficients _parabolicBlueMotorCoefficients = {
            .lowCutoffRotorFreq = 3,
            .a =  0.0087,
            .b = -0.1443,
            .c =  1.708,
        };

        static inline const ParabolicModelCoefficients _parabolicModelAmpCoeff = _parabolicBlueMotorCoefficients;

        static inline const SlipCoefficients _blueMotorSlipCoefficients = {
            .startFreqHz = 3, 
            .startCutoffRotorFreq = 1,
            .linearCutoffRotorFreq = 16,
            .m = -0.022,
            .b = 0.62,
            .highSlip = 0.26,
        };  

        static inline const SlipCoefficients _slipCoeff = _blueMotorSlipCoefficients;
};



#endif // __cplusplus