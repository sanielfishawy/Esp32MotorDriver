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

    void testWgGetPoint(void) {
        WaveformGen::setFreqHz(1.0);
        WaveformGen::setPPAmplitudeFract(0.75);
        WaveformGen::setDcOffsetFract(0.5);

        WaveformGen::start();
        ets_delay_us(.25 * 1000 * 1000);
        WaveformGen::stop();

        int point = WaveformGen::getPoint(0);
        int expected = (int) ( (0.5 + 0.75 / 2) * WG_MAX_ADC_VALUE );
        ESP_LOGI("testWgGetPoint", "expected: %d", expected);
        TEST_ASSERT_INT_WITHIN(1, expected, point);

        point = WaveformGen::getPoint(0.25 * 2 * M_PI);
        expected = (int) ( 0.5 * WG_MAX_ADC_VALUE );
        TEST_ASSERT_INT_WITHIN(1, expected, point);
    }

    void run_test_WaveformGen(){
        UNITY_BEGIN();
            testWaveformGenSetUp();
            RUN_TEST(testWgGetPoint);
            testWaveformGenTearDown();
        UNITY_END();
    }

}