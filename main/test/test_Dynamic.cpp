extern "C" {
    #include "unity.h"
}

#include "esp_err.h"
#include "esp_log.h"
#include "cJSON.h"

#include "../tuning/Dynamic.h"
#include "../http/HttpServer.h"

extern "C" {

    static void test_dynamicSetupMeasurementFromJson() {
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

    static void test_dynamicRun() {
        HttpServer::setup();
        Dynamic::setup();
        // Dynamic::Measurement measurement = {
        //     .minFreqHz = 4,
        //     .maxFreqHz = 10,
        //     .slipFract = 0.2,
        //     .amplitudeFract = 0.5,
        //     .startTime = 0,
        //     .endTime = 0
        // };
        // Dynamic::setupMeasurement(measurement);
    }

    void run_test_Dynamic(){
        UNITY_BEGIN();
        // RUN_TEST(test_dynamicSetupMeasurementFromJson);
        RUN_TEST(test_dynamicRun);
        UNITY_END();
    }

}