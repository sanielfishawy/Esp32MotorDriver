#include "Spiffs.h"

bool Spiffs::_isSetup = false;

void Spiffs::setup(){
    if (_isSetup) return;

    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true
    };

    const char *TAG = "Spiffs";
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        ESP_ERROR_CHECK(ret);
    }
    ESP_LOGI(TAG, "SPIFFS mounted");
    
    _isSetup = true;
}