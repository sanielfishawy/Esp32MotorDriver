#include "Routes.h"

std::vector<httpd_uri_t> Routes::uris = {
    {
        .uri       = "/amplitudeFract",
        .method    = HTTP_GET,
        .handler   = RouteHandlers::getAmplitudeFractHandler,
        .user_ctx  = nullptr,
    },
    {
        .uri       = "/amplitudeFract",
        .method    = HTTP_PUT,
        .handler   = RouteHandlers::setAmplitudeFractHandler,
        .user_ctx  = nullptr,
    },
    {
        .uri       = "/freqHz",
        .method    = HTTP_GET,
        .handler   = RouteHandlers::getFreqHzHandler,
        .user_ctx  = nullptr,
    },
    {
        .uri       = "/freqHz",
        .method    = HTTP_PUT,
        .handler   = RouteHandlers::setFreqHzHandler,
        .user_ctx  = nullptr,
    },
    {
        .uri       = "/setFloat",
        .method    = HTTP_PUT,
        .handler   = RouteHandlers::setFloatHandler,
        .user_ctx  = nullptr,
    },
    {
        .uri       = "/setActive",
        .method    = HTTP_PUT,
        .handler   = RouteHandlers::setActiveHandler,
        .user_ctx  = nullptr,
    },
    {
        .uri       = "/isActive",
        .method    = HTTP_GET,
        .handler   = RouteHandlers::getIsActiveHandler,
        .user_ctx  = nullptr,
    }
};