extern "C" {
    #include "unity.h"
}

#include <math.h>
#include "../models/PhaseGen.h"
#include "esp_log.h"
#include "rom/ets_sys.h"

static void testPhaseGenSetUp(){
    PhaseGen::setup();
}

static void testPhaseGenTearDown(){
    PhaseGen::tearDown();
}

extern "C" {

    static void testPgSetPeriod(void) {
        TEST_ASSERT_EQUAL_INT(PhaseGen::getPeriodTicks(), PG_MAX_PERIOD_TICKS);
        PhaseGen::setFreqHz(PG_MAX_FREQ_HZ * 1.05);
        TEST_ASSERT_EQUAL_INT(PhaseGen::getPeriodTicks(), PG_MIN_PERIOD_TICKS);
        PhaseGen::setFreqHz(PG_MIN_FREQ_HZ * 0.95);
        TEST_ASSERT_EQUAL_INT(PhaseGen::getPeriodTicks(), PG_MAX_PERIOD_TICKS);
    }

    static void testPgSetFreqHz(void) {
        PhaseGen::setFreqHz(0.5);

        PhaseGen::start();
        ets_delay_us(1 * 1000 * 1000);
        PhaseGen::stop();

        int periodTicks = PhaseGen::getPeriodTicks();
        TEST_ASSERT_EQUAL_INT(periodTicks, 2 * 40 * 1000000 );
        float radians = PhaseGen::getPhaseRad();
        uint64_t timerTick = PhaseGen::getTimerTick();
        float fraction = radians / (2 * M_PI);
        float fractionOfCurrentPeriodUsingTicks = (float) timerTick / periodTicks; 

        TEST_ASSERT_DOUBLE_WITHIN(0.001, radians, 0.5 * 2 * M_PI);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.5, fraction);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.5, fractionOfCurrentPeriodUsingTicks);

        PhaseGen::setFreqHz(10);
        periodTicks = PhaseGen::getPeriodTicks();
        TEST_ASSERT_EQUAL_INT(periodTicks, 0.1 * 40 * 1000000 );
        radians = PhaseGen::getPhaseRad();
        fraction = radians / (2 * M_PI);
        timerTick = PhaseGen::getTimerTick();
        fractionOfCurrentPeriodUsingTicks = (float) timerTick / periodTicks; 

        TEST_ASSERT_DOUBLE_WITHIN(0.001, radians, 0.5 * 2 * M_PI);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.5, fraction);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.5, fractionOfCurrentPeriodUsingTicks);

        PhaseGen::start();
        ets_delay_us(0.1 * 0.25 * 1000 * 1000);
        // vTaskDelay(pdMS_TO_TICKS(25));  
        PhaseGen::stop();

        radians = PhaseGen::getPhaseRad(); 
        TEST_ASSERT_EQUAL_INT(PhaseGen::getPeriodTicks(), 0.1 * 40 * 1000000 );
        TEST_ASSERT_DOUBLE_WITHIN(0.05, 0.75 * 2 * M_PI, radians);
    }

    

    void run_test_PhaseGen(){
        UNITY_BEGIN();
            testPhaseGenSetUp();
            RUN_TEST(testPgSetPeriod);
            testPhaseGenTearDown();

            testPhaseGenSetUp();
            RUN_TEST(testPgSetFreqHz);
            testPhaseGenTearDown();
        UNITY_END();
    }

}