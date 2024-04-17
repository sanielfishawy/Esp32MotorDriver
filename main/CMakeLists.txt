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
                        "test/test_Temp.cpp"
                        ${SHARED_SOURCES}
                INCLUDE_DIRS 
                        ${SHARED_INCLUDES}
                REQUIRES 
                        ${SHARED_PRIVATE_REQUIRES}
                        unity
        ) 
endif()

