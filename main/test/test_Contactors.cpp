extern "C" {
    #include "unity.h"
}

#include "cJSON.h" 
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../models/Contactors.h"

extern "C" {

    static void test_contactors() {
        cJSON *status; 
        status = Contactors::getStatusJson();
        ESP_LOGI(CT_TAG, "status: %s", cJSON_Print(status)); 

        Contactors::powerUp();
        vTaskDelay(100 / portTICK_PERIOD_MS);

        status = Contactors::getStatusJson();
        ESP_LOGI(CT_TAG, "status: %s", cJSON_Print(status)); 
    }

    void run_test_Contactors(){
        UNITY_BEGIN();
        RUN_TEST(test_contactors);
        UNITY_END();
    }

}