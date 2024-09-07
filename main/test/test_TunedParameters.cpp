extern "C" {
    #include "unity.h"
}

#include "esp_log.h"
#include "../models/TunedParameters.h"
#define TTP_TAG "test_TunedParameters"

extern "C" {

    static void test_tunedParameters() {

        TEST_ASSERT_DOUBLE_WITHIN(0.01, 3, TunedParameters::getFreqHzForMaxTorqueWithRotorFreq(.99));
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 14, TunedParameters::getFreqHzForMaxTorqueWithRotorFreq(10));
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 30*(1 + .26), TunedParameters::getFreqHzForMaxTorqueWithRotorFreq(30));
        
        // See pythonTuning project or desmos for expected values.
        float torque = 1;
        float rotorSpeed = 4;
        float amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(torque, rotorSpeed);
        ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        // TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.8, amplitudeFract);

        torque = 1;
        rotorSpeed = 16;
        amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(torque, rotorSpeed);
        ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        // TEST_ASSERT_DOUBLE_WITHIN(0.2, 0.7, amplitudeFract);

        torque = 1;
        rotorSpeed = 40;
        amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(torque, rotorSpeed);
        ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        // TEST_ASSERT_DOUBLE_WITHIN(0.01, 1, amplitudeFract);

        torque = 0.5;
        rotorSpeed = 15;
        amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(torque, rotorSpeed);
        ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);

        torque = 1.0;
        rotorSpeed = 0;
        amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(torque, rotorSpeed);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.75, amplitudeFract);
        // ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        
        torque = 1.0;
        rotorSpeed = 2.9;
        amplitudeFract = TunedParameters::getAmplitudeFractWithTorqueAndRotorFreq(torque, rotorSpeed);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, 0.75, amplitudeFract);
        // ESP_LOGI(TTP_TAG, "torque: %f, rotorSpeed: %f, amplitudeFract: %f", torque, rotorSpeed, amplitudeFract);
        
    }

    void run_test_TunedParameters(){
        UNITY_BEGIN();
        RUN_TEST(test_tunedParameters);
        UNITY_END();
    }

}