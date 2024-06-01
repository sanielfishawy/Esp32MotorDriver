extern "C" {
    #include "unity.h"
}

#include <math.h>
#include "esp_timer.h"
#include "../models/SvPwm.h"
#include "esp_log.h"

extern "C" {

    static void test_svPwm() {
        SvPwmAll all;

        int64_t start, stop;

        // SvPwmPulse pulse;
        SvPwmPulses pulses;

        float amp = 1.0;
        float theta = 0;
        start = esp_timer_get_time();
        SvPwm svPwmx(theta, amp);
        svPwmx.pulses(&pulses); 
        stop = esp_timer_get_time();
        ESP_LOGI(SV_PWM_TAG, "SvPwmx took %lld us", stop - start);

        amp = 1.0;
        theta = 0;
        start = esp_timer_get_time();
        SvPwm svPwm0(theta, amp);
        svPwm0.pulses(&pulses); 
        stop = esp_timer_get_time();
        ESP_LOGI(SV_PWM_TAG, "SvPwm0 took %lld us", stop - start);
        svPwm0.getAll(&all);
        TEST_ASSERT_EQUAL_INT(1, all.sector);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0335, all.pulses.aPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.9330, all.pulses.aPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.4665, all.pulses.bPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0669, all.pulses.bPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.4665, all.pulses.cPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0669, all.pulses.cPulse.pw);

        amp = 1.0;
        theta = M_PI/6;
        start = esp_timer_get_time();
        SvPwm svPwm1(theta, amp);
        svPwm1.pulses(&pulses);
        stop = esp_timer_get_time();
        svPwm1.getAll(&all);
        ESP_LOGI(SV_PWM_TAG, "SvPwm1 took %lld us", stop - start);
        TEST_ASSERT_EQUAL_INT(1, all.sector);
        TEST_ASSERT_EQUAL_FLOAT(0.5, all.zeroDegT);
        TEST_ASSERT_EQUAL_FLOAT(0.5, all.sixtyDegT);
        TEST_ASSERT_EQUAL_FLOAT(0.0, all.pulses.aPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(1.0, all.pulses.aPulse.pw);
        TEST_ASSERT_EQUAL_FLOAT(0.25, all.pulses.bPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(0.5, all.pulses.bPulse.pw);
        TEST_ASSERT_EQUAL_FLOAT(0.5, all.pulses.cPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(0, all.pulses.cPulse.pw);

        amp = 0.5;
        theta = M_PI/6;
        start = esp_timer_get_time();
        SvPwm svPwm2(theta, amp);
        svPwm2.pulses(&pulses);
        stop = esp_timer_get_time();
        svPwm2.getAll(&all);
        ESP_LOGI(SV_PWM_TAG, "SvPwm2 took %lld us", stop - start);
        TEST_ASSERT_EQUAL_INT(1, all.sector);
        TEST_ASSERT_EQUAL_FLOAT(0.25, all.zeroDegT);
        TEST_ASSERT_EQUAL_FLOAT(0.25, all.sixtyDegT);
        TEST_ASSERT_EQUAL_FLOAT(0.125, all.aPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(0.75, all.pulses.aPulse.pw);
        TEST_ASSERT_EQUAL_FLOAT(0.25, all.pulses.bPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(0.5, all.pulses.bPulse.pw);
        TEST_ASSERT_EQUAL_FLOAT(0.375, all.pulses.cPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(.25, all.pulses.cPulse.pw);

        amp = 1.0;
        theta = M_PI/2;
        start = esp_timer_get_time();
        SvPwm svPwm3(theta, amp);
        svPwm3.pulses(&pulses);
        stop = esp_timer_get_time();
        svPwm3.getAll(&all);
        ESP_LOGI(SV_PWM_TAG, "SvPwm3 took %lld us", stop - start);
        TEST_ASSERT_EQUAL_FLOAT(0.25, all.pulses.aPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(0.50, all.pulses.aPulse.pw);
        TEST_ASSERT_EQUAL_FLOAT(0, all.pulses.bPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(1, all.pulses.bPulse.pw);
        TEST_ASSERT_EQUAL_FLOAT(0.5, all.pulses.cPulse.edge);
        TEST_ASSERT_EQUAL_FLOAT(0, all.pulses.cPulse.pw);

        amp = 1.0;
        theta = 5*M_PI/6;
        start = esp_timer_get_time();
        SvPwm svPwm5(theta, amp);
        svPwm5.pulses(&pulses); 
        stop = esp_timer_get_time();
        ESP_LOGI(SV_PWM_TAG, "SvPwm5 took %lld us", stop - start);
        svPwm5.getAll(&all);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.aPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.aPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.bPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 1, all.pulses.bPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.25, all.pulses.cPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.cPulse.pw);

        amp = 1.0;
        theta = 7*M_PI/6;
        start = esp_timer_get_time();
        SvPwm svPwm7(theta, amp);
        svPwm7.pulses(&pulses);
        stop = esp_timer_get_time();
        ESP_LOGI(SV_PWM_TAG, "SvPwm7 took %lld us", stop - start);
        svPwm7.getAll(&all);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.aPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.aPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.25, all.pulses.bPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.bPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.cPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 1, all.pulses.cPulse.pw);

        amp = 1.0;
        theta = 9*M_PI/6;
        start = esp_timer_get_time();
        SvPwm svPwm9(theta, amp);
        svPwm9.pulses(&pulses);
        stop = esp_timer_get_time();
        ESP_LOGI(SV_PWM_TAG, "SvPwm9 took %lld us", stop - start);
        stop = esp_timer_get_time();
        svPwm9.getAll(&all);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.25, all.pulses.aPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.aPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.bPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.bPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.cPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 1, all.pulses.cPulse.pw);

        amp = 1.0;
        theta = 11*M_PI/6;
        start = esp_timer_get_time();
        SvPwm svPwm11(theta, amp);
        svPwm11.pulses(&pulses);
        stop = esp_timer_get_time();
        ESP_LOGI(SV_PWM_TAG, "SvPwm11 took %lld us", stop - start);
        svPwm11.getAll(&all);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.aPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 1, all.pulses.aPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.bPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0, all.pulses.bPulse.pw);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.25, all.pulses.cPulse.edge);
        TEST_ASSERT_FLOAT_WITHIN(.001, 0.5, all.pulses.cPulse.pw);
    }

    void run_test_SvPwm(){
        UNITY_BEGIN();
        RUN_TEST(test_svPwm);
        UNITY_END();
    }

}