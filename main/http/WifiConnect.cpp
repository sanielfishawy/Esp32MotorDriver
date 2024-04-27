#include "WifiConnect.h"

#define DEFAULT_SSID "scoutandjagger"
#define DEFAULT_PWD "ridgebacks"


const char * WifiConnect::_logTag = "WifiConnect";
bool WifiConnect::_isSetup = false;

void WifiConnect::setup() {
    if (_isSetup) return;

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    _scan();

    _isSetup = true;
}

void WifiConnect::_eventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_LOGI(_logTag, "started");
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED) {
        ESP_LOGI(_logTag, "connected");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(_logTag, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
    }
}


void WifiConnect::_scan() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &_eventHandler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &_eventHandler, NULL, NULL));

    // Initialize default station as network interface instance (esp-netif)
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    // Initialize and start WiFi
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "scoutandjagger",
            .password = "ridgebacks",
            .scan_method = WIFI_FAST_SCAN,
            // .sort_method = WIFI_CONNECT_AP_BY_SIGNAL,
            // .threshold.rssi = DEFAULT_RSSI,
            // .threshold.authmode = DEFAULT_AUTHMODE,
        },
    };
    #pragma GCC diagnostic push
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}
