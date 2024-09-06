#include "RouteHandlers.h"
esp_err_t RouteHandlers::rootHandler(httpd_req_t *req){
    cJSON *responseObj = cJSON_CreateObject();
    cJSON_AddBoolToObject(responseObj, "ok", true);
    cJSON_AddBoolToObject(responseObj, "isActive", VFD::getIsActive());
    cJSON_AddNumberToObject(responseObj, "amplitudeFract", VFD::getAmplitudeFract());
    cJSON_AddNumberToObject(responseObj, "freqHz", VFD::getFreqHz());
    cJSON_AddNumberToObject(responseObj, "rotorSpeedHz", VFD::getRotorSpeedHz());
    cJSON_AddNumberToObject(responseObj, "electricalEquivalentSpeedHz", VFD::getRotorElectricalEquivalentSpeedHz());
    cJSON_AddNumberToObject(responseObj, "slipHz", VFD::getSlipHz());
    cJSON_AddNumberToObject(responseObj, "slipFract", VFD::getSlipFract());
    cJSON_AddNumberToObject(responseObj, "torqueFract", TorqueControl::getTorque());
    cJSON_AddBoolToObject(responseObj, "useGoPedal", TorqueControl::getUseGoPedal());
    cJSON_AddItemToObject(responseObj, "goPedalStatus", GoPedal::getStatus());
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
        return _sendResponse(req, _getInvalidParamResponseObject(), "400 Bad Request");
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
        return _sendResponse(req, _getInvalidParamResponseObject(), "400 Bad Request");
    }
    VFD::setFreqHz(value);
    cJSON *resultObject = _getFloatResultObject("freqHz", VFD::getFreqHz());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getTorqueHandler(httpd_req_t *req){
    cJSON *resultObject = _getFloatResultObject("torqueFract", TorqueControl::getTorque());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::setTorqueHandler(httpd_req_t *req){
    float value;
    if (!_getFloatValueParam(req, &value)) {
        return _sendResponse(req, _getInvalidParamResponseObject(), "400 Bad Request");
    }
    TorqueControl::setTorque(value);
    cJSON *resultObject = _getFloatResultObject("torqueFract", TorqueControl::getTorque());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getUseGoPedalHandler(httpd_req_t *req){
    cJSON *resultObject = _getBoolResultObject("useGoPedal", TorqueControl::getUseGoPedal());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::setUseGoPedalHandler(httpd_req_t *req){
    bool value;
    if (!_getBoolValueParam(req, &value)) {
        return _sendResponse(req, _getInvalidParamResponseObject(), "400 Bad Request");
    }
    TorqueControl::setUseGoPedal(value);
    cJSON *resultObject = _getBoolResultObject("useGoPedal", TorqueControl::getUseGoPedal());
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getGoPedalStatusHandler(httpd_req_t *req){
    cJSON *resultObject = GoPedal::getStatus();
    return _sendResponse(req, resultObject);
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

esp_err_t RouteHandlers::setDynamicMeasurementHandler(httpd_req_t *req){
    cJSON *jsonObj = NULL;

    esp_err_t err = _getPostJson(req, &jsonObj);
    if (err != ESP_OK){
        if (jsonObj != NULL) cJSON_Delete(jsonObj); 
        _sendResponse(req, _getErrorResponseObject("Error getting JSON from POST body"), "400 Bad Request");
        return err;
    } 

    err = Dynamic::setupMeasurementFromJson(jsonObj);
    if (err != ESP_OK){
        if (jsonObj != NULL) cJSON_Delete(jsonObj); 
        _sendResponse(req, _getErrorResponseObject("Error setting dynamic measurement. See ESP logs for details."), "400 Bad Request");
        return err;
    }
    
    _sendResponse(req, _getOkResponseObject(jsonObj));
    return err;
}

esp_err_t RouteHandlers::getStaticTorqueMeasurementHandler(httpd_req_t *req){
    int torque = StaticTorqueMeasurement::getTorque();
    cJSON *resultObject = _getFloatResultObject("torque", torque);
    cJSON *responseObj = _getOkResponseObject(resultObject);
    return _sendResponse(req, responseObj);
}

esp_err_t RouteHandlers::getDynamicMeasurementHandler(httpd_req_t *req){
    cJSON *measurement = Dynamic::getMeasurementJson();
    cJSON *responseObj = _getOkResponseObject(measurement);
    return _sendResponse(req, responseObj);
}

cJSON *RouteHandlers::_getInvalidParamResponseObject() {
    return _getErrorResponseObject("Invalid or missing parameter");
}

cJSON *RouteHandlers::_getErrorResponseObject(const char *message) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddBoolToObject(root, "ok", false);
    cJSON_AddStringToObject(root, "error", message);
    return root;
}

cJSON *RouteHandlers::_getOkResponseObject(cJSON *resultObject) {
    cJSON *root = cJSON_CreateObject();
    // ESP_LOGI(ROUTE_HANDLERS_TAG, "resultObject: %s", cJSON_Print(resultObject));
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
        *value = _parseFloat(param_value, &success);
        if (success) return true;
        else return false;
    }
    return false;
}

bool RouteHandlers::_getBoolValueParam(httpd_req_t *req, bool *value) {
    char uri_params[HS_MAX_URI_LENGTH] = {0};

    httpd_req_get_url_query_str(req, uri_params, HS_MAX_URI_LENGTH);
    char param_value[HS_MAX_PARAM_LENGTH];

    if (httpd_query_key_value(uri_params, "value", param_value, sizeof(param_value)) == ESP_OK) {
        // Convert the parameter string to a boolean
        if (strcasecmp(param_value, "true") == 0 || strcmp(param_value, "1") == 0) {
            *value = true;
            return true;
        } else if (strcasecmp(param_value, "false") == 0 || strcmp(param_value, "0") == 0) {
            *value = false;
            return true;
        }
    }

    return false;
}

float RouteHandlers::_parseFloat(const char* str, bool* success) {
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

esp_err_t _getPostData(httpd_req_t *req, char **buf) {
    int totalLen = req->content_len;
    int currLen = 0;
    int received = 0;
    *buf = (char *) malloc(totalLen + 1); // Plus one for null termination
    if (*buf == NULL) {
        ESP_LOGE(ROUTE_HANDLERS_TAG, "Failed to allocate memory for post buffer");
        return ESP_ERR_NO_MEM;
    }

    while (currLen < totalLen) {
        received = httpd_req_recv(req, *buf + currLen, totalLen - currLen);
        if (received <= 0) { 
            ESP_LOGE(ROUTE_HANDLERS_TAG, "Error getting post body data");
            free(*buf);
            return ESP_FAIL;
        }
        currLen += received;
    }
    (*buf)[totalLen] = '\0'; // Null-terminate the buffer
    return ESP_OK;
}

esp_err_t RouteHandlers::_getJsonFromString(char **jsonStr, cJSON **json){

    if (*jsonStr == NULL) {
        ESP_LOGE(ROUTE_HANDLERS_TAG, "JSON string is NULL");
        return ESP_ERR_INVALID_ARG;
    }

    *json = cJSON_Parse(*jsonStr);
    if (*json == NULL) {
        ESP_LOGE(ROUTE_HANDLERS_TAG, "Error parsing JSON string");
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t RouteHandlers::_getPostJson(httpd_req_t *req, cJSON **json) {
    char *jsonStr = NULL;
    esp_err_t err = _getPostData(req, &jsonStr);
    
    if (err != ESP_OK) return err; // No mem allocated if error. 

    err = _getJsonFromString(&jsonStr, json);
    free(jsonStr); 
    return err;
}



