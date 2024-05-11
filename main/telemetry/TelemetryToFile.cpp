#include "TelemetryToFile.h"


bool TelemetryToFile::_isSetup = false;

void TelemetryToFile::setup() {
    if (_isSetup) return;
    Spiffs::setup();
    _isSetup = true;
}

esp_err_t TelemetryToFile::writeDataPoint(const char *filename, DataPoint *dp) {
    setup();
    
    FILE *file;
    size_t writePos = WritePosition::loadWritePos(filename);
    if (writePos == -1) {
        writePos = 0;
        file = fopen(filename, "w+b");
        ESP_LOGD(TEL_TAG, "Creating new file: %s, pointer%p", filename, (void*)file);
    } else {
        file = fopen(filename, "r+b");
        ESP_LOGD(TEL_TAG, "Opening existing file: %s, pointer%p", filename, (void*)file);
    }
    if (!file){
        ESP_LOGE(TEL_TAG, "Failed to open file for writing:  %s", filename);
        return ESP_FAIL;
    } 

    size_t dpSize = sizeof(DataPoint);

    fseek(file, writePos, SEEK_SET);
    fwrite(dp, dpSize, 1, file);
    fflush(file);
    fclose(file);

    writePos += dpSize;
    if (writePos >= TEL_FILE_SIZE) {
        writePos = 0;  
    }
    WritePosition::saveWritePos(filename, writePos);
    return ESP_OK;
}


esp_err_t TelemetryToFile::readDataPoints(const char *filename, DataPoint **dataPoints, size_t *numPoints) {
    setup();

    FILE *file = fopen(filename, "rb");
    if (!file){
        ESP_LOGD(TEL_TAG, "Failed to open file for reading:  %s", filename);
        *dataPoints = NULL; 
        return ESP_OK;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    *numPoints = fileSize / sizeof(DataPoint);
    *dataPoints = (DataPoint *)malloc(fileSize);

    if (*dataPoints == NULL) {
        fclose(file);
        return ESP_FAIL;  // Memory allocation failed
    }

    size_t readSize = fread(*dataPoints, sizeof(DataPoint), *numPoints, file);
    fclose(file);

    if (readSize != *numPoints) {
        free(*dataPoints);
        return ESP_FAIL;  // File read error
    }

    return ESP_OK;
}
