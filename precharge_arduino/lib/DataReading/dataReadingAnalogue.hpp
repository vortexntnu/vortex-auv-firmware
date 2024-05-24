#include <Arduino.h>

#define NUM_SAMPLES 100 // The bigger the number, less prone to noise, but longer

class DataReadingAnalogue {
private:
    float samples[NUM_SAMPLES];
    int sampleIndex;
    int pin;

    float readVoltage();
    float movingAverageFilter(float newSample);

public:
    DataReadingAnalogue(int pin);
    ~DataReadingAnalogue();

    float getFilteredVoltage();
    float getRawVoltage();
};