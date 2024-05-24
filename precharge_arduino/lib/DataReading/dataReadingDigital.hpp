#include <Arduino.h>

#define NUM_SAMPLES 50 // The bigger the number, less prone to noise, but longer

class DataReadingDigital {
private:
    bool samples[NUM_SAMPLES];
    int sampleIndex;
    int pin;

    bool readState();
    bool movingAverageFilter(bool newSample);

public:
    DataReadingDigital(int pin);
    ~DataReadingDigital();

    bool getFilteredState();
    bool getRawState();
};