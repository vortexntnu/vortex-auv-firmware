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
1. Make a new directory and cd into it
```
mkdir ~/pico
cd ~/pico
```
2. Clone the master branch for the sdk and have it up to date: 
```
git clone https://github.com/raspberrypi/pico-sdk.git
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

