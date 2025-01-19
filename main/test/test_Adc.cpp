extern "C" {
    #include "unity.h"
}

#include "../models/Adc.h"

extern "C" {

    static void test_adc() {
        int val = Adc::readRaw((adc_channel_t) ADC1_GPIO1_CHANNEL);
        ESP_LOGI(ADC_TAG, "ADC1 CH1: %d", val);
    }

    void run_test_Adc(){
        UNITY_BEGIN();
        RUN_TEST(test_adc);
        UNITY_END();
    }

}