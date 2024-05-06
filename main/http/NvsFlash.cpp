#include "NvsFlash.h"

bool NvsFlash::_isSetup = false;

void NvsFlash::setup() {
    if (_isSetup) return;

        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            err = nvs_flash_init();
        }
        ESP_ERROR_CHECK(err);
        _isSetup = true;
}