#pragma once

#include <errno.h>
#include <string.h>

#include "esp_http_server.h"
#include "cJSON.h"
#include "esp_err.h"

#include "Vfd.h"
#include "SvPwm.h"

#ifdef __cplusplus
    
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
        
        private:
            static esp_err_t _sendResponse(httpd_req_t *req, cJSON *responseObj, const char* status="200 OK");
            static cJSON *_getOkResponseObject(cJSON *resultObject);
            static cJSON *_getErrorResponseObject(const char *message);
            static cJSON *_getFloatResultObject(const char * key, float value);
            static cJSON *_getBoolResultObject(const char * key, bool value);
            static bool _getFloatValueParam(httpd_req_t *req, float *value);
            static bool _getStringParam(httpd_req_t *req, const char *paramName, char *value, size_t valueSize);
            static float _parse_float(const char* str, bool* success);

    };

#endif // __cplusplus