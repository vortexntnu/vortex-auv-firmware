#include "dataReading.hpp"

// Builder for the class
DataReading::DataReading(int inputPin) {
    pin = inputPin;
    sampleIndex = 0;

    // Set the list with 0 in case memory we allocated had something inside of it from before
    for (int i = 0; i < NUM_SAMPLES; i++) {
        this->samples[i] = 0;
    }
}

// Destructor is empty as we dont dynamically allocate memory or use some black magic C++ memory stuff
DataReading::~DataReading() {}

// Private Methods
float DataReading::readVoltage() {
    int analogValue = analogRead(this->pin);
    return (analogValue * 5.0) / 1023.0;
}

float DataReading::movingAverageFilter(int newSample) {
    this->samples[this->sampleIndex] = newSample;
    this->sampleIndex = (this->sampleIndex + 1) % NUM_SAMPLES;

    int sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += this->samples[i];
    }
    return (float)sum / NUM_SAMPLES;
}

// Public Method
float DataReading::getFilteredVoltage() {
    float voltage = readVoltage();
    return movingAverageFilter(voltage);
}
