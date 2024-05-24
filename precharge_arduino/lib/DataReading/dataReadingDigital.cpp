#include "dataReadingDigital.hpp"

// Builder for the class
DataReadingDigital::DataReadingDigital(int inputPin) {
    pin = inputPin;
    sampleIndex = 0;

    // Set the list with 0 in case memory we allocated had something inside of it from before
    for (int i = 0; i < NUM_SAMPLES; i++) {
        this->samples[i] = 0.0;
    }
}

// Destructor is empty as we dont dynamically allocate memory or use some black magic C++ memory stuff
DataReadingDigital::~DataReadingDigital() {}

// Private Methods
bool DataReadingDigital::readState() {
    bool digitalValue = digitalRead(this->pin);
    return digitalValue;
}

bool DataReadingDigital::movingAverageFilter(bool newSample) {
    this->samples[this->sampleIndex] = newSample;
    this->sampleIndex = (this->sampleIndex + 1) % NUM_SAMPLES;

    int sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += (int)(this->samples[i]);
    }
    return (bool)(sum / NUM_SAMPLES);
}

// Public Method
bool DataReadingDigital::getFilteredState() {
    bool state = readState();
    bool stateFiltered = movingAverageFilter(state);
    return stateFiltered;
}

bool DataReadingDigital::getRawState() {
    bool state = readState();
    return state;
}
