extern "C" {
    #include "unity.h"
}

#include "PhaseGenTimer.h"
#include "esp_log.h"    
#include "rom/ets_sys.h"


static void testPhaseGenTimerSetUp(){
    PhaseGenTimer::setup();
    PhaseGenTimer::startTimer();
}

static void testPhaseGenTearDown(){
    PhaseGenTimer::tearDown();
}

extern "C" {
    
    static void test_pgTimerSetupTeardown(){
        PhaseGenTimer::tearDown();
        PhaseGenTimer::setup();
        TEST_ASSERT_EQUAL_INT64(0, PhaseGenTimer::getTick());
        PhaseGenTimer::tearDown();
    }
    
    static void test_PhaseGenTimer() {
        uint64_t tick; 

        ets_delay_us(1000 * 1000);
        tick = PhaseGenTimer::getTick();
        TEST_ASSERT_UINT64_WITHIN(1000, 40000000, tick);

        PhaseGenTimer::setTick(0);
        tick = PhaseGenTimer::getTick();
        TEST_ASSERT(tick < 1000);

        ets_delay_us(2 * 1000 * 1000);
        tick = PhaseGenTimer::getTick();
        TEST_ASSERT_UINT64_WITHIN(1000, 80000000, tick);
    }

    void run_test_PhaseGenTimer(){
        UNITY_BEGIN();
            testPhaseGenTimerSetUp();
            RUN_TEST(test_pgTimerSetupTeardown);
            testPhaseGenTearDown();

            testPhaseGenTimerSetUp();
            RUN_TEST(test_PhaseGenTimer);
            testPhaseGenTearDown();
        UNITY_END();
    }

}