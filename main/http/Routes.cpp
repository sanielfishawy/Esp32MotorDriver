#include "Routes.h"

std::vector<httpd_uri_t> Routes::uris = {
    {
        .uri       = "/",
        .method    = HTTP_GET,
        .handler   = RouteHandlers::rootHandler,
        .user_ctx  = nullptr,
    },
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
    },
    {
        .uri      = "/getFile",
        .method   = HTTP_GET,
        .handler  = RouteHandlers::getFileHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/svPwm",
        .method   = HTTP_GET,
        .handler  = RouteHandlers::getSvPwmHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/setDynamicMeasurement",
        .method   = HTTP_POST,
        .handler  = RouteHandlers::setDynamicMeasurementHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/getDynamicMeasurement",
        .method   = HTTP_GET,
        .handler  = RouteHandlers::getDynamicMeasurementHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/getMeasuredStaticTorque",
        .method   = HTTP_GET,
        .handler  = RouteHandlers::getStaticTorqueMeasurementHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/torque",
        .method   = HTTP_PUT,
        .handler  = RouteHandlers::setTorqueHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/torque",
        .method   = HTTP_GET,
        .handler  = RouteHandlers::getTorqueHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/useGoPedal",
        .method   = HTTP_PUT,
        .handler  = RouteHandlers::setUseGoPedalHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/useGoPedal",
        .method   = HTTP_GET,
        .handler  = RouteHandlers::getUseGoPedalHandler,
        .user_ctx = nullptr,
    },
    {
        .uri      = "/goPedalStatus",
        .method   = HTTP_GET,
        .handler  = RouteHandlers::getGoPedalStatusHandler,
        .user_ctx = nullptr,
    },
};