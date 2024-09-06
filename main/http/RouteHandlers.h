#pragma once

#include <errno.h>
#include <string.h>
#include <stdbool.h>


#include "esp_http_server.h"
#include "cJSON.h"
#include "esp_err.h"

#include "Vfd.h"
#include "SvPwm.h"
#include "Dynamic.h"
#include "StaticTorqueMeasurement.h"
#include "TorqueControl.h"
#include "GoPedal.h"

#ifdef __cplusplus

#define ROUTE_HANDLERS_TAG "RouteHandlers"
    
    class RouteHandlers{
        public:
            static esp_err_t rootHandler(httpd_req_t *req);
            static esp_err_t getAmplitudeFractHandler(httpd_req_t *req);
            static esp_err_t setAmplitudeFractHandler(httpd_req_t *req);
            static esp_err_t getFreqHzHandler(httpd_req_t *req);
            static esp_err_t setFreqHzHandler(httpd_req_t *req);
            static esp_err_t setFloatHandler(httpd_req_t *req);
            static esp_err_t setActiveHandler(httpd_req_t *req);
            static esp_err_t getIsActiveHandler(httpd_req_t *req);
            static esp_err_t getFileHandler(httpd_req_t *req);
            static esp_err_t getSvPwmHandler(httpd_req_t *req);
            static esp_err_t setDynamicMeasurementHandler(httpd_req_t *req);
            static esp_err_t getDynamicMeasurementHandler(httpd_req_t *req);
            static esp_err_t getStaticTorqueMeasurementHandler(httpd_req_t *req);
            static esp_err_t setTorqueHandler(httpd_req_t *req);
            static esp_err_t getTorqueHandler(httpd_req_t *req);
            static esp_err_t setUseGoPedalHandler(httpd_req_t *req);
            static esp_err_t getUseGoPedalHandler(httpd_req_t *req);
            static esp_err_t getGoPedalStatusHandler(httpd_req_t *req);
        
        private:
            static esp_err_t _sendResponse(httpd_req_t *req, cJSON *responseObj, const char* status="200 OK");
            static cJSON *_getOkResponseObject(cJSON *resultObject);
            static cJSON *_getErrorResponseObject(const char *message);
            static cJSON *_getInvalidParamResponseObject();
            static cJSON *_getFloatResultObject(const char * key, float value);
            static cJSON *_getBoolResultObject(const char * key, bool value);
            static bool _getFloatValueParam(httpd_req_t *req, float *value);
            static bool _getBoolValueParam(httpd_req_t *req, bool *value);
            static bool _getStringParam(httpd_req_t *req, const char *paramName, char *value, size_t valueSize);
            static float _parseFloat(const char* str, bool* success);
            static esp_err_t _getJsonFromString(char **jsonStr, cJSON **json);
            static esp_err_t _getPostJson(httpd_req_t *req, cJSON **json);
    };

#endif // __cplusplus