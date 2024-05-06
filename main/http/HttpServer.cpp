#include "HttpServer.h"


bool HttpServer::_isSetup = false;

httpd_uri_t HttpServer::_hello = {
    .uri       = "/hello",
    .method    = HTTP_GET,
    .handler   = _get_hello_handler,
    .user_ctx  = NULL
};

void HttpServer::setup(){
    if (_isSetup) return;

    NvsFlash::setup();
    WifiConnect::setup();
    _start_webserver();

    _isSetup = true;
}

esp_err_t HttpServer::_get_hello_handler(httpd_req_t *req) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "message", "Hello, world!");
    const char *response = cJSON_Print(root);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response, strlen(response));

    free((void *)response);
    cJSON_Delete(root);
    return ESP_OK;
}


httpd_handle_t HttpServer::_start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &_hello);
    }
    return server;
}


