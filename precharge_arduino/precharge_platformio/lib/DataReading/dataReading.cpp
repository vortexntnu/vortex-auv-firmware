#include "dataReading.hpp"

DataReading::DataReading(int pin) : pin(pin), sampleIndex(0) {
    for (int i = 0; i < NUM_SAMPLES; i++) {
        this->samples[i] = 0;
    }
}

DataReading::~DataReading() {}

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

float DataReading::getFilteredVoltage() {
    float voltage = readVoltage();
    return movingAverageFilter(voltage);
}
