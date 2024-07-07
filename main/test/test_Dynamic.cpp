extern "C" {
    #include "unity.h"
}

#include "esp_err.h"
#include "cJSON.h"

#include "../tuning/Dynamic.h"

extern "C" {

    static void test_dynamic() {
        // Dynamic::setup();
        esp_err_t err = Dynamic::setupMeasurementFromJson(NULL);
        TEST_ASSERT_EQUAL(ESP_ERR_INVALID_ARG, err);

        cJSON *measurement = cJSON_CreateObject();
        err = Dynamic::setupMeasurementFromJson(measurement);
        TEST_ASSERT_EQUAL(ESP_ERR_INVALID_ARG, err);

        cJSON_AddNumberToObject(measurement, "minFreqHz", 0.0); 
        err = Dynamic::setupMeasurementFromJson(measurement);
        TEST_ASSERT_EQUAL(ESP_ERR_INVALID_ARG, err);

        cJSON_AddNumberToObject(measurement, "maxFreqHz", 0.0);
        err = Dynamic::setupMeasurementFromJson(measurement);
        TEST_ASSERT_EQUAL(ESP_ERR_INVALID_ARG, err);

        cJSON_AddNumberToObject(measurement, "slipFract", 0.0);
        err = Dynamic::setupMeasurementFromJson(measurement);
        TEST_ASSERT_EQUAL(ESP_ERR_INVALID_ARG, err);
        
        cJSON_AddNumberToObject(measurement, "amplitudeFract", 0.0);
        err = Dynamic::setupMeasurementFromJson(measurement);
        TEST_ASSERT_EQUAL(ESP_OK, err);
    }

    void run_test_Dynamic(){
        UNITY_BEGIN();
        RUN_TEST(test_dynamic);
        UNITY_END();
    }

}