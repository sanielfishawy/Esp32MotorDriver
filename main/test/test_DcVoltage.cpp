extern "C" {
    #include "unity.h"
}

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../models/DcVoltage.h"

extern "C" {

    static void test_dcVoltage() {
        // int val;
        // float sum = 0;
        // int i = 0;
        // float avg;
        while(1){
            // i++;
            float val = DCVoltage::readVoltage();
            // sum += val;
            // avg = sum / i;
            // ESP_LOGI(DCV_TAG, "av: %f val: %d", avg, val);
            ESP_LOGI(DCV_TAG, "val: %f", val);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    void run_test_DcVoltage(){
        UNITY_BEGIN();
        RUN_TEST(test_dcVoltage);
        UNITY_END();
    }

}