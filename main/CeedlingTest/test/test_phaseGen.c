#include <math.h>
#include <stdio.h>
#include "unity.h"
#include "../models/PhaseGen.h"

void setUp(void) {
}

void tearDown(void) {
}

void testPGSetPeriod(void) {
    TEST_ASSERT_EQUAL_INT(PhaseGen::_periodTicks, PG_MAX_PERIOD_TICKS);
    // PG_setPeriod(0);
    // TEST_ASSERT_EQUAL_INT(PG_MIN_PERIOD, PG_period);
    // PG_setPeriod(PG_MAX_PERIOD + 1);
    // TEST_ASSERT_EQUAL_INT(PG_MAX_PERIOD, PG_period);
}

void testPGHandlePwmTick(void) {
    // PG_setPeriod(400);
    // sendTicks(1);
    // TEST_ASSERT_EQUAL_INT(0, PG_phaseFraction());
    // sendTicks(100);
    // TEST_ASSERT_EQUAL_FLOAT(0.25, PG_phaseFraction());
    // sendTicks(500);
    // TEST_ASSERT_EQUAL_FLOAT(0.5, PG_phaseFraction());

    // PG_setPeriod(4000);
    // sendTicks(1);
    // TEST_ASSERT_EQUAL_FLOAT(0.5, PG_phaseFraction());
    // TEST_ASSERT_EQUAL_INT(2000, PG_phaseTickNum());
    // TEST_ASSERT_EQUAL_UINT64(2000, PG_timestamp);
    // TEST_ASSERT_EQUAL_FLOAT(0.5 * 2 * M_PI, PG_phaseRadians());
}
