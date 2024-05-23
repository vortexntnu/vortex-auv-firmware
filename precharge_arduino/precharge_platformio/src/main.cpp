#include <Arduino.h>
#include "dataReading.hpp"



// Definitions and Global Variables (START) ==================================================
// Define relay output pins
#define RELAY_XAVIER                   2
#define RELAY_THRUSTERS_3_AND_4        3
#define RELAY_THRUSTERS_1_AND_2        4
#define RELAY_FAILSAFE                 8
#define RELAY_PDB                      9

// Voltage thresholds
#define XAVIER_THRESHOLD               4.75 // Voltage
#define THRUSTER_THRESHOLD             2.4  // Voltage
#define PDB_THRESHOLD                  4.75 // Voltage

// Voltage measurement pins
#define VOLTAGE_XAVIER                 A2
#define VOLTAGE_THRUSTER_3_AND_4       A3
#define VOLTAGE_THRUSTER_1_AND_2       A4
#define VOLTAGE_PDB                    A5

// Create instances of DataReading for each pin
DataReading xavier(VOLTAGE_XAVIER);
DataReading thruster34(VOLTAGE_THRUSTER_3_AND_4);
DataReading thruster12(VOLTAGE_THRUSTER_1_AND_2);
DataReading pdb(VOLTAGE_PDB);

// Create Functions for use later
void controlRelay(float voltage, float thresholdVoltage, uint8_t relayPin);
// Definitions and Global Variables (STOP) ==================================================



// Setup (START) ==================================================
void setup() {
    // Set up relay pins as outputs
    pinMode(RELAY_XAVIER, OUTPUT);
    pinMode(RELAY_THRUSTERS_3_AND_4, OUTPUT);
    pinMode(RELAY_THRUSTERS_1_AND_2, OUTPUT);
    pinMode(RELAY_FAILSAFE, OUTPUT);
    pinMode(RELAY_PDB, OUTPUT);

    // Initialize all relays to off
    digitalWrite(RELAY_XAVIER, LOW);
    digitalWrite(RELAY_THRUSTERS_3_AND_4, LOW);
    digitalWrite(RELAY_THRUSTERS_1_AND_2, LOW);
    digitalWrite(RELAY_FAILSAFE, LOW);
    digitalWrite(RELAY_PDB, LOW);
}
// Setup (STOP) ==================================================



// Main Loop (START) ==================================================
void loop() {
    // Get filtered voltages
    float xavierVoltage = xavier.getFilteredVoltage();
    float thruster34Voltage = thruster34.getFilteredVoltage();
    float thruster12Voltage = thruster12.getFilteredVoltage();
    float pdbVoltage = pdb.getFilteredVoltage();

    // Check and control relays based on voltage readings
    controlRelay(xavierVoltage, XAVIER_THRESHOLD, RELAY_XAVIER);
    controlRelay(thruster34Voltage, THRUSTER_THRESHOLD, RELAY_THRUSTERS_3_AND_4);
    controlRelay(thruster12Voltage, THRUSTER_THRESHOLD, RELAY_THRUSTERS_1_AND_2);
    controlRelay(pdbVoltage, PDB_THRESHOLD, RELAY_PDB);

    // A small delay to avoid rapid toggling
    delayMicroseconds(100);
}
// Main Loop (STOP) ==================================================



// Functions (START) ==================================================
void controlRelay(float voltage, float thresholdVoltage, uint8_t relayPin) {
    if (voltage >= thresholdVoltage) {
        digitalWrite(relayPin, HIGH);
    } else {
        digitalWrite(relayPin, LOW);
    }
}
// Functions (STOP) ==================================================
