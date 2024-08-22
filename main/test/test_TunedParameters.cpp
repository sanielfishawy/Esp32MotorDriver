extern "C" {
    #include "unity.h"
}

#include "esp_log.h"
#include "../models/TunedParameters.h"
#define TTP_TAG "test_TunedParameters"

extern "C" {

    static void test_tunedParameters() {
        for (float rotorSpeed = 0; rotorSpeed < 30; rotorSpeed += 1){
            float slip = TunedParameters::_getSlip(rotorSpeed);
            float freqHz = TunedParameters::getFreqHzForMaxTorqueWithRotorSpeed(rotorSpeed);
            // ESP_LOGI(TTP_TAG, "rotorSpeed: %f, slip: %f, freqHz: %f", rotorSpeed, slip, freqHz);
        }

        TEST_ASSERT_DOUBLE_WITHIN(0.01, 3, TunedParameters::getFreqHzForMaxTorqueWithRotorSpeed(.99));
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 14, TunedParameters::getFreqHzForMaxTorqueWithRotorSpeed(10));
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 30*(1 + .26), TunedParameters::getFreqHzForMaxTorqueWithRotorSpeed(30));
        
        // See pythonTuning project for expected values.
        float torque = 0.8;
        float rotorSpeed = 4;
        float amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorSpeed(torque, rotorSpeed);
        // ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.8, amplitudeFract);

        torque = 0.22;
        rotorSpeed = 16;
        amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorSpeed(torque, rotorSpeed);
        // ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        TEST_ASSERT_DOUBLE_WITHIN(0.2, 0.7, amplitudeFract);

        torque = 0.5;
        rotorSpeed = 40;
        amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorSpeed(torque, rotorSpeed);
        // ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 1, amplitudeFract);
    }

    void run_test_TunedParameters(){
        UNITY_BEGIN();
        RUN_TEST(test_tunedParameters);
        UNITY_END();
    }

}