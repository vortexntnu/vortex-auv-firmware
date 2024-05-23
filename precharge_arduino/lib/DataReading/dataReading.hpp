#include <Arduino.h>

#define NUM_SAMPLES 10

class DataReading {
private:
    int samples[NUM_SAMPLES];
    int sampleIndex;
    int pin;

    float readVoltage();
    float movingAverageFilter(int newSample);

public:
    DataReading(int pin);
    ~DataReading();
    float getFilteredVoltage();
};