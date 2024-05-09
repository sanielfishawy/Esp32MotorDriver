#pragma once

#include "esp_http_server.h"
#include "cJSON.h"
#include <errno.h>

#include "Vfd.h"

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
        
        private:
            static esp_err_t _sendResponse(httpd_req_t *req, cJSON *responseObj, const char* status="200 OK");
            static cJSON *_getOkResponseObject(cJSON *resultObject);
            static cJSON *_getErrorResponseObject(const char *message);
            static cJSON *_getFloatResultObject(const char * key, float value);
            static cJSON *_getBoolResultObject(const char * key, bool value);
            static bool _getFloatValueParam(httpd_req_t *req, float *value);
            static float _parse_float(const char* str, bool* success);

    };

#endif // __cplusplus