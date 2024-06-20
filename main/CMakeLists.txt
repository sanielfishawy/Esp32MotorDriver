set (
        SHARED_SOURCES
                "models/PwmPairs.cpp"
                "models/McPwmInterrupt.cpp"
                "models/Adc.cpp"
                "models/PhaseGenTimer.cpp"
                "models/PhaseGen.cpp"
                "models/Integrator.cpp"
                "models/Derivator.cpp"
                "models/Pid.cpp"
                "models/Vfd.cpp"
                "models/FastLog.cpp"
                "models/McPwmPair.cpp"
                "models/SvPwm.cpp"
                "models/Quadrature.cpp"
                "models/RotorSpeed.cpp"
                "http/WifiConnect.cpp"
                "http/NvsFlash.cpp"
                "http/HttpServer.cpp"
                "http/Routes.cpp"
                "http/RouteHandlers.cpp"
                "telemetry/WritePosition.cpp"
                "telemetry/TelemetryToFile.cpp"
                "telemetry/Spiffs.cpp"
)

set (
        SHARED_INCLUDES
                "."
                "models"
)

set ( 
        SHARED_PRIVATE_REQUIRES
                driver
                esp_timer
                esp_adc
                esp_wifi
                nvs_flash
                esp_http_server
                json
                mdns
                spiffs
)

if (NOT DEFINED ENV{TEST_COMPONENT})
        idf_component_register( 
                SRCS    
                        "app_main.c"
                        ${SHARED_SOURCES}
                INCLUDE_DIRS 
                        ${SHARED_INCLUDES}
                PRIV_REQUIRES 
                        ${SHARED_PRIVATE_REQUIRES}
        )
endif()


if(DEFINED ENV{TEST_COMPONENT})
        idf_component_register(
                SRCS 
                        "test/test_runner.cpp"
                        "test/test_PhaseGenTimer.cpp"
                        "test/test_PhaseGen.cpp"
                        "test/test_Integrator.cpp"
                        "test/test_Derivator.cpp"
                        "test/test_Pid.cpp"
                        "test/test_Calibrate.cpp"
                        "test/test_Vfd.cpp"
                        "test/test_WifiConnect.cpp"
                        "test/test_HttpServer.cpp"
                        "test/test_WritePosition.cpp"
                        "test/test_TelemetryToFile.cpp"
                        "test/test_Spiffs.cpp"
                        "test/test_McPwmPair.cpp"
                        "test/test_PwmPairs.cpp"
                        "test/test_SvPwm.cpp"
                        ${SHARED_SOURCES}
                INCLUDE_DIRS 
                        ${SHARED_INCLUDES}
                REQUIRES 
                        ${SHARED_PRIVATE_REQUIRES}
                        unity
        ) 
endif()

