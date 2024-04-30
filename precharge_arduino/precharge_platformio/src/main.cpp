#include <Arduino.h>

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

  for(uint8_t i = 4; (i < 10 && (i != 6 || i != 5)); i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(XAVI_VLM, INPUT);
  pinMode(ESC2_VLM, INPUT);
  pinMode(ESC1_VLM, INPUT);
  pinMode(PDB_VLM, INPUT);
}

void loop() {
  float ESC1_VLM = analogRead(ESC1_VLM);
  float ESC2_VLM = analogRead(ESC2_VLM);

  ESC1_VLM = map(ESC1_VLM, 0, 1023, 0, 5);
  ESC2_VLM = map(ESC2_VLM, 0, 1023, 0, 5);

  float XAVI_VLM = analogRead(XAVI_VLM);
  float PDB_VLM = analogRead(PDB_VLM);

  int F_STATE = digitalRead(CTRL);

  XAVI_VLM = map(XAVI_VLM, 0, 1023, 0, 5);
  PDB_VLM = map(PDB_VLM, 0, 1023, 0, 5);

  if(F_STATE) {
    digitalWrite(REL_FS, LOW);
  } else {
    digitalWrite(REL_FS, HIGH);
  }

  check_voltage(XAVI_VLM, REL_XAVI);
  check_voltage(PDB_VLM, REL_PDB);
  check_voltage_ESC(ESC1_VLM, REL_2STAT);
  check_voltage_ESC(ESC2_VLM, REL_1STAT);
  watchdog();
}


void check_voltage(float voltage, uint8_t pin) {
  if(voltage >= 4.75) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

void check_voltage_ESC(float voltage, uint8_t pin) {
  if(voltage >= 2.4) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

void watchdog() {
  static uint32_t last_millis = 0;
  if(millis() - last_millis > 1000) {
    last_millis = millis();
    for(uint8_t i = 0; i < 5; i++) {
      analogRead(i);
    }
  }
}
