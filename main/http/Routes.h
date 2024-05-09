#pragma once

#include <vector>

#include "esp_http_server.h"
#include "RouteHandlers.h"

#ifdef __cplusplus

class Routes {
    public:
        static std::vector<httpd_uri_t> uris;

    private:

};

#endif // __cplusplus