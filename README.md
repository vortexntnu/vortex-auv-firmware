# vortex-auv-firmware
Firmware for the Autonomous Underwater Vehicle

# I2C
For changing I2C pins look at this short video to see how you can easily change pins on Raspberri Pi Pico MCU
Link: https://www.youtube.com/watch?v=APvtNK66shM&ab_channel=ShotokuTech


## PSM RPI PICO Library

Utilises the official SDK for Raspberry Pi Pico and reads two analog values from the PSM module, convert the analog voltage values to their actually representation for current and voltage, and then send them over I2C to the main Raspberry Pi on the system. The I2C address for the Pico is 0x69. 

To use this code, follow these steps:
1. cd into the directory
2. run the build.sh file, which will make a new directory called build, cd into that directory, run cmake for configuration, and then make for building the code.
3. Inside the newly made build directory, you should find a file called psm_rpi_pico.uf2 which can be dragged and dropped into the Raspberry Pi Pico. 

In order for the previous steps to work fully, you need to have done the following: 
#### 1. Installed and configured the Pico SDK:
1. Make a new directory and cd into it, we will call it pico and have it in home. You can chose another name, another directory, or another path if you wish just make sure to take that into account for the next steps. 
```
mkdir ~/pico
cd ~/pico
```
2. Clone the master branch for the sdk and have it up to date: 
```
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
```
3. Configure the PATH for sdk; you can either do it globaly inside bashrc or you can declare it manually in the terminal everytime before using the sdk. To declare it globaly, either do the following on the terminal or simply copy paste everythomg netweem the single quote after echo to the end of .bashrc file and restart the terminal. 
```
echo 'export PICO_SDK_PATH=/home/<replace_with_username>/pico/pico-sdk'
source ~/.bashrc
```
#### 2. Install cmake alongside the necessary dependencies and the compiler
1. Make sure everything is up to date
```
sudo apt update
```
2. Install the compilers and the libraries. This might take a while depending on how fast are your pc and internet. 
```
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

If you want to ponder upon some examples of how the SDK is used or implemented for the various API's, you can either read the documentation found at: 

https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf?_gl=1*s1qhsn*_ga*MTg3OTAyOTg0MC4xNzE3NDE5NTI0*_ga_22FD70LWDS*MTcxNzQ5Njc5My4yLjAuMTcxNzQ5Njc5My4wLjAuMA.. 

Or you can read through the examples found at this repo: 
https://github.com/raspberrypi/pico-examples.git

If you decide to change something that might require a new or different librarby, please make sure to have that library configured as a library to include inside the CMakeLists.txt file. 