#pragma once

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

#include "DataPoint.h"
#include "WritePosition.h"
#include "Spiffs.h"
#include "../appConfig.h"

#define TEL_FILE_SIZE (size_t) ( TEL_NUM_POINTS_STORED * sizeof(DataPoint) ) 

#ifdef __cplusplus

class TelemetryToFile{
    public:
        static void setup();
        static esp_err_t writeDataPoint(const char *filename, DataPoint *dp);
        static esp_err_t readDataPoints(const char *filename, DataPoint **dataPoints, size_t *numPoints);

    private:
        static bool _isSetup;
};

#endif // __cplusplus



