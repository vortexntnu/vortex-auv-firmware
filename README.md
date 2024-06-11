# vortex-auv-firmware
Firmware for the Autonomous Underwater Vehicle

# I2C
For changing I2C pins look at this short video to see how you can easily change pins on Raspberri Pi Pico MCU
Link: https://www.youtube.com/watch?v=APvtNK66shM&ab_channel=ShotokuTech


# PSM RPI PICO Library

This library utilizes the official SDK for the Raspberry Pi Pico to read two analog values from the PSM module. It converts these analog voltage values to their respective real values for current and voltage and sends them over I2C to the main Raspberry Pi in the system. The I2C address for the Pico is `0x69`.

## Prerequisites

Before using this code, ensure you have completed the following:

1. **Installed and configured the Pico SDK:**
    1. Create a new directory and navigate into it. We'll call it `pico` and place it in the home directory. You can choose another name, directory, or path, but ensure you adjust subsequent steps accordingly:
        ```bash
        mkdir ~/pico
        cd ~/pico
        ```
    2. Clone the master branch of the SDK and update submodules:
        ```bash
        git clone -b master https://github.com/raspberrypi/pico-sdk.git
        cd pico-sdk
        git submodule update --init
        ```
    3. Configure the PATH for the SDK. You can either set it globally in `.bashrc` or declare it manually in the terminal before using the SDK. To set it globally, add the following line to `.bashrc` and restart the terminal:
        ```bash
        echo 'export PICO_SDK_PATH=/home/<replace_with_username>/pico/pico-sdk' >> ~/.bashrc
        source ~/.bashrc
        ```

2. **Installed CMake along with necessary dependencies and the compiler:**
    1. Ensure your package list is up to date:
        ```bash
        sudo apt update
        ```
    2. Install the compilers and libraries (this might take some time depending on your PC and internet speed):
        ```bash
        sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
        ```

## Building the Code

To compile and configure the code for your Raspberry Pi Pico, follow these steps:

1. Navigate to the project directory:
    ```bash
    cd <name_of_directory>
    ```
    Alternatively, you can open the directory in VSCode and use the integrated terminal.

2. Run the `build.sh` script, which automates the following steps:
    - Creates a new directory called `build`
    - Navigates into that directory
    - Runs CMake for configuration
    - Runs `make` to build the code

    To run the `build.sh` file:
    ```bash
    ./build.sh
    ```

3. Inside the newly created `build` directory, you should find a file named `psm_rpi_pico.uf2`. This file can be dragged and dropped onto the Raspberry Pi Pico in debug mode. To enter debug mode:
    - Hold the BOOTSEL button on the board before connecting it to the PC.
    - Keep holding the button until the PC recognizes the Pico as an HID (Human Interface Device).

    If this does not work, ensure that you have a data-capable USB cable (not just power).

## Additional Information

### Documentation and Examples

For more details on how the SDK is used or implemented for various APIs, refer to the official documentation:

- [Raspberry Pi Pico C/C++ SDK Documentation](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)

You can also explore practical examples provided in the following repository:

- [Raspberry Pi Pico Examples](https://github.com/raspberrypi/pico-examples)

### Modifying the Code

If you decide to make changes that require new or different libraries, ensure to configure the library correctly and include it in the `CMakeLists.txt` file.

---

Feel free to reach out if you encounter any issues or need further assistance!
