#include "TestOutputPin.h"

// Private attributes
TestOutputPin* TestOutputPin::_instance = nullptr;
SemaphoreHandle_t TestOutputPin::_mutex = nullptr;

// Public methods
TestOutputPin* TestOutputPin::getInstance() {
    if (_mutex == nullptr) {
        initializeMutex(); 
    }

    xSemaphoreTake(_mutex, portMAX_DELAY);
    if (_instance == nullptr) {
        _instance = new TestOutputPin();
    }
    xSemaphoreGive(_mutex); 

    return _instance;
}

void TestOutputPin::setLevel(int level) {
    ESP_ERROR_CHECK(gpio_set_level(TEST_OUTPUT_GPIO_NUM, level));
}

// Protected methods
TestOutputPin::TestOutputPin() {
    ESP_ERROR_CHECK(gpio_reset_pin(TEST_OUTPUT_GPIO_NUM));
    ESP_ERROR_CHECK(gpio_set_direction(TEST_OUTPUT_GPIO_NUM, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_intr_disable(TEST_OUTPUT_GPIO_NUM));
    ESP_ERROR_CHECK(gpio_set_pull_mode(TEST_OUTPUT_GPIO_NUM, GPIO_PULLUP_PULLDOWN));
    ESP_ERROR_CHECK(gpio_set_drive_capability(TEST_OUTPUT_GPIO_NUM, GPIO_DRIVE_CAP_3));
}


// Private methods
void TestOutputPin::initializeMutex() {
    static bool isMutexInitialized = false;
    if (!isMutexInitialized) {
        _mutex = xSemaphoreCreateMutex();
        isMutexInitialized = true;
    }
}
