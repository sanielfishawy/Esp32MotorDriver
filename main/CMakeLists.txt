set (
        SHARED_SOURCES
                "setup.cpp"
                "models/Temp.cpp"
                "models/PwmTimer.cpp"
                "models/PwmPin.cpp"
                "models/PwmPair.cpp"
                "models/PwmPairs.cpp"
                "models/PwmInterrupt.cpp"
                "models/TestOutputPin.cpp"
                "models/PwmInterruptPin.cpp"
                "models/Adc.cpp"
                "models/PhaseGenTimer.cpp"
                "models/PhaseGen.cpp"
                "models/WaveformGen.cpp"
                "models/Integrator.cpp"
                "models/Derivator.cpp"
                "models/Pid.cpp"
                "models/Vfd.cpp"
                "models/OpenLoopClosedLoop.cpp"
                "models/FastLog.cpp"
                "models/ChargePump.cpp"
                "http/WifiConnect.cpp"
                "http/NvsFlash.cpp"
                "http/HttpServer.cpp"
                "http/Routes.cpp"
                "http/RouteHandlers.cpp"
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
                        "test/test_Temp.cpp"
                        "test/test_PhaseGenTimer.cpp"
                        "test/test_PhaseGen.cpp"
                        "test/test_WaveformGen.cpp"
                        "test/test_Integrator.cpp"
                        "test/test_Derivator.cpp"
                        "test/test_Pid.cpp"
                        "test/test_Calibrate.cpp"
                        "test/test_Hardware.cpp"
                        "test/test_Vfd.cpp"
                        "test/test_ChargePump.cpp"
                        "test/test_Performance.cpp"
                        "test/test_WifiConnect.cpp"
                        "test/test_HttpServer.cpp"
                        ${SHARED_SOURCES}
                INCLUDE_DIRS 
                        ${SHARED_INCLUDES}
                REQUIRES 
                        ${SHARED_PRIVATE_REQUIRES}
                        unity
        ) 
endif()

