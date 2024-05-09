extern "C" {
    #include "unity.h"
}

#include <math.h>
#include "../models/WaveformGen.h"
#include "esp_log.h"
#include "rom/ets_sys.h"

static void testWaveformGenSetUp(){
    WaveformGen::setup();
}

static void testWaveformGenTearDown(){
    WaveformGen::tearDown();
}

extern "C" {

    static void testWgGetPoint(void) {
        WaveformGen::setFreqHz(1.0);
        WaveformGen::setAmplitudeFract(0.75);

        WaveformGen::start();
        ets_delay_us(.25 * 1000 * 1000);
        WaveformGen::stop();

        float duty = WaveformGen::getDuty(0);
        float expected = 0.75;
        TEST_ASSERT_EQUAL_FLOAT(expected, duty);

        duty = WaveformGen::getDuty(0.25 * 2 * M_PI);
        expected = 0;
        TEST_ASSERT_FLOAT_WITHIN(0.001, expected, duty);
    }

    void run_test_WaveformGen(){
        UNITY_BEGIN();
            testWaveformGenSetUp();
            RUN_TEST(testWgGetPoint);
            testWaveformGenTearDown();
        UNITY_END();
    }

}