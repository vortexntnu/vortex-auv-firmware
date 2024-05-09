#include <Arduino.h>
#include <avr/wdt.h>

#define REL_XAVI  2
#define REL_2STAT 3
#define REL_1STAT 4
#define CTRL      7
#define REL_FS    8
#define REL_PDB   9

#define XAVI_VLM  A2
#define ESC2_VLM  A3
#define ESC1_VLM  A4
#define PDB_VLM   A5

void setup() {
  // Set up control pins as outputs
  wdt_disable();
  
  pinMode(REL_XAVI, OUTPUT);
  pinMode(REL_2STAT, OUTPUT);
  pinMode(REL_1STAT, OUTPUT);
  pinMode(REL_FS, OUTPUT);
  pinMode(REL_PDB, OUTPUT);

  // Set up sensor pins as inputs
  pinMode(XAVI_VLM, INPUT);
  pinMode(ESC2_VLM, INPUT);
  pinMode(ESC1_VLM, INPUT);
  pinMode(PDB_VLM, INPUT);
  
  wdt_enable(WDTO_2S);
}


void loop() {
  int esc1Value = analogRead(ESC1_VLM);
  int esc2Value = analogRead(ESC2_VLM);
  int xaviValue = analogRead(XAVI_VLM);
  int pdbValue = analogRead(PDB_VLM);

  float esc1Voltage = mapVoltage(esc1Value);
  float esc2Voltage = mapVoltage(esc2Value);
  float xaviVoltage = mapVoltage(xaviValue);
  float pdbVoltage = mapVoltage(pdbValue);

  int fState = digitalRead(CTRL);
  digitalWrite(REL_FS, fState ? LOW : HIGH);

  checkVoltage(xaviVoltage, REL_XAVI);
  checkVoltage(pdbVoltage, REL_PDB);
  checkVoltageESC(esc1Voltage, REL_2STAT);
  checkVoltageESC(esc2Voltage, REL_1STAT);

  wdt_reset();
}

float mapVoltage(int analogValue) {
  return (analogValue * 5.0) / 1023.0;
}

void checkVoltage(float voltage, uint8_t pin) {
  digitalWrite(pin, voltage >= 4.75 ? HIGH : LOW);
}

void checkVoltageESC(float voltage, uint8_t pin) {
  digitalWrite(pin, voltage >= 2.4 ? HIGH : LOW);
}

/*
void watchdog() {
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 1000) {
    // Reset the watchdog timer
    lastMillis = millis();

    // Potentially reset the system or signal an error
    reset system();
  }
}

void resetSystem() {
  // Enable Watchdog Timer with a very short timeout
  wdt_enable(WDTO_15MS);

  // Enter an infinite loop to cause the watchdog to reset the system
  while (true) {}
}
*/

