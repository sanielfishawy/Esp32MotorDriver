extern "C" {
    #include "unity.h"
}

#include "cJSON.h" 
#include "esp_log.h"

#include "../models/Contactors.h"

extern "C" {

    static void test_contactors() {
        cJSON *status; 
        status = Contactors::getStatusJson();
        ESP_LOGI(CT_TAG, "status: %s", cJSON_Print(status)); 

        Contactors::powerUp();

        status = Contactors::getStatusJson();
        ESP_LOGI(CT_TAG, "status: %s", cJSON_Print(status)); 
    }

    void run_test_Contactors(){
        UNITY_BEGIN();
        RUN_TEST(test_contactors);
        UNITY_END();
    }

}