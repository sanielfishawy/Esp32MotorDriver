#!/bin/bash

# Define the IDF project directory
PROJECT_DIR="${HOME}/dev/espProjects/Esp32MotorDriver/"

# Define the port your device is connected to
SERIAL_PORT="/dev/cu.usbmodem14101"

# Navigate to the project directory
cd "$PROJECT_DIR"

# Export the TEST_COMPONENT environment variable
export TEST_COMPONENT=1

# Build the project
idf.py build

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "Build successful, flashing the device..."
    
    # Flash the device
    idf.py -p $SERIAL_PORT flash

    # Check if flash was successful
    if [ $? -eq 0 ]; then
        echo "Flashing successful, running monitor..."
        
        # Run monitor
        idf.py -p $SERIAL_PORT monitor
    else
        echo "Flashing failed."
    fi
else
    echo "Build failed."
fi
