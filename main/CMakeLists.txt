idf_component_register(SRCS "app_main.c"
                            "models/PwmPair.cpp"
                            "models/PwmPin.cpp"
                            "models/PwmTimer.cpp"
                            "models/PwmInterrupt.cpp"
                    INCLUDE_DIRS "." "models"
                    PRIV_REQUIRES driver)
