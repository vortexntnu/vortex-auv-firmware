#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/i2c_slave.h"

// ADC pins for Raspberry Pi Pico
#define VOLTAGE_SENSE_PIN 29
#define CURRENT_SENSE_PIN 28

// I2C configuration
static const uint I2C_SLAVE_ADDRESS = 0x17;
#define SDA_PIN 26
#define SCL_PIN 27

// Constants based on the PSM specs
#define VOLTAGE_SENSE_FACTOR 11.0  // 11.0 V/V
#define CURRENT_SENSE_FACTOR 37.8788  // 37.8788 A/V
#define CURRENT_SENSE_OFFSET 0.330  // 0.330V

// Array to hold the voltage and current readings
static float readings[2] = {0.0f, 0.0f};

// Function to convert ADC reading to voltage (in Volts)
float adc_to_voltage(uint16_t adc_value) {
    return adc_value * (3.3f / (1 << 12));  // 3.3V reference, 12-bit ADC resolution
}

// Function to convert voltage reading to actual voltage
float calculate_actual_voltage(float adc_voltage) {
    return adc_voltage * VOLTAGE_SENSE_FACTOR;
}

// Function to convert voltage reading to actual current
float calculate_actual_current(float adc_current) {
    return (adc_current - CURRENT_SENSE_OFFSET) * CURRENT_SENSE_FACTOR;
}

static void i2c_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch(event) {
        case I2C_SLAVE_REQUEST:
            i2c_write_byte_raw(i2c, ((uint8_t *)readings)[0]);
            i2c_write_byte_raw(i2c, ((uint8_t *)readings)[1]);
            break;

        case I2C_SLAVE_FINISH:
            break;
    }
}

static void i2c_setup() {
    gpio_init(SDA_PIN);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_init(SCL_PIN);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);

    i2c_init(i2c1, 100000);  // 100 kHz I2C frequency
    i2c_slave_init(i2c1, I2C_SLAVE_ADDRESS, &i2c_handler);
}

int main() {
    // Initialize stdio and ADC
    stdio_init_all();
    adc_init();

    // Configure ADC pins
    adc_gpio_init(VOLTAGE_SENSE_PIN);
    adc_gpio_init(CURRENT_SENSE_PIN);

    // Initialize I2C
    i2c_setup();

    uint8_t buffer[8];  // Buffer to hold voltage and current readings

    while (1) {
        // Select and read the voltage sense ADC pin
        adc_select_input(0);
        uint16_t adc_voltage_raw = adc_read();

        // Select and read the current sense ADC pin
        adc_select_input(1);
        uint16_t adc_current_raw = adc_read();

        // Convert raw ADC values to voltages
        float voltage_sense_voltage = adc_to_voltage(adc_voltage_raw);
        float current_sense_voltage = adc_to_voltage(adc_current_raw);

        // Calculate actual voltage and current
        float actual_voltage = calculate_actual_voltage(voltage_sense_voltage);
        float actual_current = calculate_actual_current(current_sense_voltage);

        // Prepare data to send over I2C
        memcpy(buffer, &actual_voltage, sizeof(float));
        memcpy(buffer + sizeof(float), &actual_current, sizeof(float));

        // Update the readings array
        memcpy(readings, buffer, sizeof(buffer));

        // Print the results (or send to master system)
        printf("Actual Voltage: %.2f V\n", actual_voltage);
        printf("Actual Current: %.2f A\n", actual_current);

        // Delay before next reading
        sleep_ms(1000);
    }

    return 0;
}
