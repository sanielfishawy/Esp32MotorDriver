#include "Contactors.h"

bool Contactors::_isSetup = false; 

void Contactors::powerUp() {
    _setup();

    int i = 0;
    _dcDisChgOff();

    while (DCVoltage::readVoltage() < CT_VOLTAGE_HI_THRESHOLD) {
        if (i%10 == 0) ESP_LOGI(CT_TAG, "Charging waiting for voltage to rise from: %f, to threshold: %f", DCVoltage::readVoltage(), CT_VOLTAGE_HI_THRESHOLD);
        i++;
        _dcOff();
        _dcChgOn();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    _dcChgOff();
    _dcOn();
}

void Contactors::powerDown() {
    _setup();

    _dcOff();
    _dcChgOff();
    _dcDisChgOn();
}

Contactors::State Contactors::getState(){
    _setup();

    if (_isOn()) {
        return State::ON;
    } else if (_isCharging()) {
        return State::CHARGING;
    } else if (_isDischarging()) {
        return State::DISCHARGING;
    } else if (_isOff()) {
        return State::OFF;
    } else {
        return State::FAULT;
    }
}

std::string Contactors::getStateString() {
    switch (getState()) {
        case State::ON:
            return "on";
        case State::CHARGING:
            return "charging";
        case State::DISCHARGING:
            return "discharging";
        case State::OFF:
            return "off";
        case State::FAULT:
            return "fault";
        default:
            return "unknown";
    }
}

cJSON *Contactors::getStatusJson() {
    _setup();
    cJSON *statusJson = cJSON_CreateObject();
    cJSON_AddStringToObject(statusJson, "state", getStateString().c_str());
    cJSON_AddNumberToObject(statusJson, "voltage", DCVoltage::readVoltage());
    cJSON_AddBoolToObject(statusJson, "dcOn", _isDcOn());
    cJSON_AddBoolToObject(statusJson, "dcChgOn", _isDcChgOn());
    cJSON_AddBoolToObject(statusJson, "dcDisChgOn", _isDcDisChgOn());
    return statusJson;
}

void Contactors::_setup() {
    if (_isSetup) return;
    _setupGpio(CT_DC_ON_GPIO_NUM);
    _setupGpio(CT_DC_CHG_GPIO_NUM);
    _setupGpio(CT_DC_DIS_CHG_GPIO_NUM);
    _dcOff();
    _dcChgOff();
    _dcDisChgOn();
    _isSetup = true;
    ESP_LOGI(CT_TAG, "is setup");
}

void Contactors::_setupGpio(gpio_num_t gpioNum) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << gpioNum),
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void Contactors::_dcOn() {
    gpio_set_level(CT_DC_ON_GPIO_NUM, 1);
}

void Contactors::_dcOff() {
    gpio_set_level(CT_DC_ON_GPIO_NUM, 0);
}

void Contactors::_dcChgOn() {
    gpio_set_level(CT_DC_CHG_GPIO_NUM, 1);
}   

void Contactors::_dcChgOff() {
    gpio_set_level(CT_DC_CHG_GPIO_NUM, 0);
}   

void Contactors::_dcDisChgOn() {
    gpio_set_level(CT_DC_DIS_CHG_GPIO_NUM, 1);
}

void Contactors::_dcDisChgOff() {
    gpio_set_level(CT_DC_DIS_CHG_GPIO_NUM, 0);
}   

bool Contactors::_isDcOn() {
    return gpio_get_level(CT_DC_ON_GPIO_NUM);
}

bool Contactors::_isDcChgOn() {
    return gpio_get_level(CT_DC_CHG_GPIO_NUM);
}

bool Contactors::_isDcDisChgOn() {
    return gpio_get_level(CT_DC_DIS_CHG_GPIO_NUM);
}

bool Contactors::_isOn() {
    return _isDcOn() && !_isDcChgOn() && !_isDcDisChgOn();
}

bool Contactors::_isCharging() {
    return !_isDcOn() && _isDcChgOn() && !_isDcDisChgOn();
}

bool Contactors::_isDischarging() {
    return !_isDcOn() && !_isDcChgOn() && _isDcDisChgOn() && DCVoltage::readVoltage() >= CT_VOLTAGE_LO_THRESHOLD;
}

bool Contactors::_isOff() {
    return !_isDcOn() && !_isDcChgOn() && _isDcDisChgOn() && DCVoltage::readVoltage() < CT_VOLTAGE_LO_THRESHOLD;
}

bool Contactors::_isFault() {
    return !_isDcOn() && !_isDcChgOn() && !_isDcDisChgOn();
}




