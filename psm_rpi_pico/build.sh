#!/bin/bash 

# Navigate to the directory of the script
cd "$(dirname "$0")"

# Remove build directory if it exists
if [ -d "build" ]; then
    rm -rf build
fi

# Create build directory
mkdir build 

# Navigate to build directory
cd build

# Run cmake and make to build the project
cmake ..
make 
