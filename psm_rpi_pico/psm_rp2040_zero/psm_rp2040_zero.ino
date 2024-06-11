// Libraties
#include <Adafruit_NeoPixel.h>
#include <Wire.h>



// Glaobal Variables
#define INTERNAL_LED_PIN 16 // Pin connected to the data input of the WS2812 LED
#define NUM_LEDS 1 // Number of LEDs in the strip (Only one internal LED lol)
#define CURRENT_ADC_PIN 29 // PSM Readings
#define VOLTAGE_ADC_PIN 28 // PSM Readings
#define I2C_SDA_PIN 26 // I2C SDA pin (GP4)
#define I2C_SCL_PIN 27 // I2C SCL pin (GP5)
#define I2C_ADDRESS 21 // I2C address of the slave device for PSM readings

int16_t currentData = 0;
int16_t voltageData = 0;
int16_t dataFrequency = 10; // [Hz]



// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel internalLED = Adafruit_NeoPixel(NUM_LEDS, INTERNAL_LED_PIN, NEO_GRB + NEO_KHZ800);



// Create custom function for sending data through I2C when requested
void requestGetPSMData();



void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  delay(1000);

  // Setup I2C communication
  Wire1.setSDA(I2C_SDA_PIN); // Set SDA pin
  Wire1.setSCL(I2C_SCL_PIN); // Set SCL pin
  Wire1.begin(I2C_ADDRESS); // Initialize I2C as a slave
  Wire1.onRequest(requestGetPSMData); // Register request handler
  delay(1000);

  // Visual debugging for clarity on startup ----------
  // Initialize the Internal RGB LED
  internalLED.begin();
  internalLED.show(); // Initialize all pixels to 'off'

  for (int8_t i = 0; i < 16; i++) {
    // Turn the LED on
    internalLED.setPixelColor(0, internalLED.Color(255, 0, 0)); // Red
    internalLED.show();
    delay(50);

    // Turn the LED off
    internalLED.setPixelColor(0, internalLED.Color(0, 0, 0)); // None
    internalLED.show();
    delay(100);
  }

  // Hold The RGB LED always on after initialization to show that the MCU has power
  internalLED.setPixelColor(0, internalLED.Color(0, 255, 0)); // Green
  internalLED.show();
}



void loop() {
  // Read PSM Data ----------
  currentData = analogRead(CURRENT_ADC_PIN);
  voltageData = analogRead(VOLTAGE_ADC_PIN);

  // Debugging ----------
  Serial.print("Current: ");Serial.print(currentData);
  Serial.print("     |     ");
  Serial.print("Voltage: ");Serial.print(voltageData);
  Serial.println();
  delay(1000/dataFrequency);
}



// Custom Functions ----------
void requestGetPSMData() {
  Wire1.write((uint8_t)(currentData >> 8)); // Send high byte of currentData
  Wire1.write((uint8_t)(currentData & 0xFF)); // Send low byte of currentData

  Wire1.write((uint8_t)(voltageData >> 8)); // Send high byte of voltageData
  Wire1.write((uint8_t)(voltageData & 0xFF)); // Send low byte of voltageData
}
