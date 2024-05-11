extern "C" {
    #include "unity.h"
}

#include <stdio.h>
#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "../telemetry/TelemetryToFile.h"
#include "../telemetry/DataPoint.h"
#include "../telemetry/FileNames.h"


extern "C" {

    static void test_telemetryToFile() {
        TelemetryToFile::setup();
        DataPoint *dataPoints = NULL;
        size_t numPoints = 0;

        remove(FN_SLIP);
        
        FILE *f = fopen(FN_SLIP, "rb");
        TEST_ASSERT_EQUAL(NULL, f);
        fclose(f);

        ESP_ERROR_CHECK(TelemetryToFile::readDataPoints(FN_SLIP, &dataPoints, &numPoints));
        TEST_ASSERT_EQUAL(NULL, dataPoints);

        for (int i = 0; i < 10; i++) {
            DataPoint dp = {
                .timestamp = esp_timer_get_time(),
                .value = (float)i
            };  
            ESP_ERROR_CHECK(TelemetryToFile::writeDataPoint(FN_SLIP, &dp));
        }

        dataPoints = NULL;
        numPoints = 0;
        ESP_ERROR_CHECK(TelemetryToFile::readDataPoints(FN_SLIP, &dataPoints, &numPoints));

        TEST_ASSERT_EQUAL(10, numPoints);

        for (int i = 0; i < numPoints; i++) {
            // ESP_LOGI("Test", "DataPoint %d: %llu, %f", i, dataPoints[i].timestamp, dataPoints[i].value);
            TEST_ASSERT_EQUAL(i, dataPoints[i].value);
        }
    }

    void run_test_TelemetryToFile(){
        UNITY_BEGIN();
        RUN_TEST(test_telemetryToFile);
        UNITY_END();
    }

}