#include "RouteHandlers.h"
esp_err_t RouteHandlers::rootHandler(httpd_req_t *req){
    cJSON *responseObj = cJSON_CreateObject();
    cJSON_AddBoolToObject(responseObj, "ok", true);
    cJSON_AddBoolToObject(responseObj, "isActive", VFD::getIsActive());
    cJSON_AddNumberToObject(responseObj, "amplitudeFract", VFD::getAmplitudeFract());
    cJSON_AddNumberToObject(responseObj, "freqHz", VFD::getFreqHz());
    cJSON_AddNumberToObject(responseObj, "rotorSpeedHz", VFD::getRotorSpeedHz());
    cJSON_AddNumberToObject(responseObj, "electricalEquivalentSpeedHz", VFD::getElectricalEquivalentSpeedHz());
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getAmplitudeFractHandler(httpd_req_t *req){
    float amp = VFD::getAmplitudeFract();
    cJSON *resultObject = _getFloatResultObject("amplitudeFract", amp);
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::setAmplitudeFractHandler(httpd_req_t *req){
    float value;

    if (!_getFloatValueParam(req, &value)) {
        cJSON *responseObj = _getErrorResponseObject("Invalid or missing value parameter");
        return _sendResponse(req, responseObj, "400 Bad Request");
    }

    VFD::setAmplitudeFract(value);
    cJSON *resultObject = _getFloatResultObject("amplitudeFract", VFD::getAmplitudeFract());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getFreqHzHandler(httpd_req_t *req){
    cJSON *resultObject = _getFloatResultObject("freqHz", VFD::getFreqHz());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::setFreqHzHandler(httpd_req_t *req){
    float value;
    if (!_getFloatValueParam(req, &value)) {
        cJSON *responseObj = _getErrorResponseObject("Invalid or missing value parameter");
        return _sendResponse(req, responseObj, "400 Bad Request");
    }
    VFD::setFreqHz(value);
    cJSON *resultObject = _getFloatResultObject("freqHz", VFD::getFreqHz());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::setFloatHandler(httpd_req_t *req){
    VFD::setFloat();
    cJSON *resultObject = _getBoolResultObject("isActive", VFD::getIsActive());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::setActiveHandler(httpd_req_t *req){
    VFD::setActive();
    cJSON *resultObject = _getBoolResultObject("isActive", VFD::getIsActive());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getIsActiveHandler(httpd_req_t *req){
    cJSON *resultObject = _getBoolResultObject("isActive", VFD::getIsActive());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getFileHandler(httpd_req_t *req){
    int filenameSize = 30;
    char filename[filenameSize];
    _getStringParam(req, "filename", filename, filenameSize);
    ESP_LOGI("getFileHandler", "filename: %s", filename);
    httpd_resp_sendstr(req, "Hello World");
    return ESP_OK;
}

esp_err_t RouteHandlers::getSvPwmHandler(httpd_req_t *req){
    cJSON *resultObject = cJSON_CreateArray();
    SvPwm::fullRevolutionAsJson(100, resultObject);  
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

cJSON *RouteHandlers::_getErrorResponseObject(const char *message) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "ok", false);
    cJSON_AddStringToObject(root, "error", message);
    return root;
}

cJSON *RouteHandlers::_getOkResponseObject(cJSON *resultObject) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "ok", true);
    cJSON_AddItemToObject(root, "results", resultObject);
    return root;
}

cJSON *RouteHandlers::_getBoolResultObject(const char * key, bool value) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, key, value);
    return root;
}

cJSON *RouteHandlers::_getFloatResultObject(const char * key, float value) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, key, value);
    return root;
}

esp_err_t RouteHandlers::_sendResponse(httpd_req_t *req, cJSON *responseObj, const char* status) {
    const char *response = cJSON_Print(responseObj);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_set_status(req, status);
    esp_err_t result = httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);

    free((void *)response);
    cJSON_Delete(responseObj);

    return result;
}

bool RouteHandlers::_getStringParam(httpd_req_t *req, const char *paramName, char *value, size_t valueSize) {
    char uri_params[HS_MAX_URI_LENGTH] = {0};

    httpd_req_get_url_query_str(req, uri_params, HS_MAX_URI_LENGTH);
    esp_err_t err = httpd_query_key_value(uri_params, paramName, value, valueSize);
    if (err == ESP_OK) {
        return true;
    }
    const char *err_str = esp_err_to_name(err);
    strncpy(value, err_str, valueSize);
    value[valueSize - 1] = '\0';
    return false;
}

bool RouteHandlers::_getFloatValueParam(httpd_req_t *req, float *value) {
    char uri_params[HS_MAX_URI_LENGTH] = {0};

    httpd_req_get_url_query_str(req, uri_params, HS_MAX_URI_LENGTH);
    char param_value[HS_MAX_PARAM_LENGTH]; 

    if (httpd_query_key_value(uri_params, "value", param_value, sizeof(param_value)) == ESP_OK) {
        bool success;
        *value = _parse_float(param_value, &success);
        if (success) return true;
        else return false;
    }
    return false;
}

float RouteHandlers::_parse_float(const char* str, bool* success) {
    char* endptr;
    errno = 0;  
    float value = strtof(str, &endptr);

    // Check for various errors
    if (errno != 0 || *endptr != '\0' || endptr == str) {
        // Handling the case where errno is set (overflow, underflow, etc.)
        // or *endptr != '\0' (not all characters were consumed, indicating invalid input)
        // or endptr == str (no characters were converted, empty string)
        *success = false;
        return 0.0f;
    }

    *success = true;
    return value;
}



