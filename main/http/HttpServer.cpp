#include "HttpServer.h"


bool HttpServer::_isSetup = false;

void HttpServer::setup(){
    if (_isSetup) return;

    NvsFlash::setup();
    WifiConnect::setup();
    _start_webserver();
    _setupMdns();

    _isSetup = true;
}

void HttpServer::_setupMdns(){
    ESP_ERROR_CHECK( mdns_init());
    ESP_ERROR_CHECK( mdns_hostname_set(HS_MDNS_HOSTNAME) );
    ESP_ERROR_CHECK( mdns_instance_name_set(HS_MDNS_INSTANCE_NAME) );
    ESP_ERROR_CHECK( mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0) );
}

httpd_handle_t HttpServer::_start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = HS_MAX_URI_HANDLERS;
    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK) {
        for (auto &uri : Routes::uris) {
            ESP_ERROR_CHECK( httpd_register_uri_handler(server, &uri) );
        }
    }
    return server;
}


