#include <Arduino.h>
#include "dataReadingAnalogue.hpp"
#include "dataReadingDigital.hpp"



// Definitions and Global Variables (START) ==================================================
// Voltage thresholds
#define THRESHOLD_XAVIER               4.75 // Recommended: 4.75 [V]
#define THRESHOLD_PDB                  4.75 // Recommended: 4.75 [V]
#define THRESHOLD_FAILSAFE             1    // Recommended: 1    [ON]
#define THRESHOLD_THRUSTER_1_AND_2     4.75 // Recommended: 4.75 [V]
#define THRESHOLD_THRUSTER_3_AND_4     4.75 // Recommended: 4.75 [V]

// Voltage measurement pins
#define VOLTAGE_XAVIER                 A2
#define VOLTAGE_PDB                    A5
#define VOLTAGE_FAILSAFE               7
#define VOLTAGE_THRUSTER_1_AND_2       A4
#define VOLTAGE_THRUSTER_3_AND_4       A3

// Define relay output pins
#define RELAY_XAVIER                   2
#define RELAY_PDB                      9
#define RELAY_FAILSAFE                 8
#define RELAY_THRUSTERS_1_AND_2        4
#define RELAY_THRUSTERS_3_AND_4        3

// Create instances of DataReading for each pin
DataReadingAnalogue Xavier(VOLTAGE_XAVIER);
DataReadingAnalogue PDB(VOLTAGE_PDB);
DataReadingDigital Failsafe(VOLTAGE_FAILSAFE);
DataReadingAnalogue Thruster1And2(VOLTAGE_THRUSTER_1_AND_2);
DataReadingAnalogue Thruster3And4(VOLTAGE_THRUSTER_3_AND_4);
// Definitions and Global Variables (STOP) ==================================================



// Setup (START) ==================================================
void setup() {
    // Debug activate
    Serial.begin(9600);

    // Set up inputs that sample voltage level
    pinMode(VOLTAGE_XAVIER, INPUT);
    pinMode(VOLTAGE_PDB, INPUT);
    pinMode(VOLTAGE_FAILSAFE, INPUT);
    pinMode(VOLTAGE_THRUSTER_1_AND_2, INPUT);
    pinMode(VOLTAGE_THRUSTER_3_AND_4, INPUT);

    // Set up relay pins as outputs
    pinMode(RELAY_XAVIER, OUTPUT);
    pinMode(RELAY_PDB, OUTPUT);
    pinMode(RELAY_FAILSAFE, OUTPUT);
    pinMode(RELAY_THRUSTERS_1_AND_2, OUTPUT);
    pinMode(RELAY_THRUSTERS_3_AND_4, OUTPUT);

    // Initialize all relays to off
    digitalWrite(RELAY_XAVIER, LOW);
    digitalWrite(RELAY_PDB, LOW);
    digitalWrite(RELAY_FAILSAFE, LOW);
    digitalWrite(RELAY_THRUSTERS_1_AND_2, LOW);
    digitalWrite(RELAY_THRUSTERS_3_AND_4, LOW);
}
// Setup (STOP) ==================================================



// Main Loop (START) ==================================================
void loop() {
    // Get filtered voltages and states
    /*
    * We use filter because the values we get are noisy 
    * And some times they can have sudden unexpected jumps upp or down that don't make sense or represent reality
    * These jumps are noise, the noise in the system is very high when the thrusters are running
    * This means that if we ran thrusters without filtering our inputs
    * Then the Precharge system could get a false negative as the noise makes the voltage dip down for a bit
    * This would cause the Precharge to think charge cut power to the thrusters
    * SO to avoid this we first filter noisy signal to make sure that the HIGH and LOW signals are real and not just noise  
    */
    float xavierVoltageFiltered = Xavier.getFilteredVoltage();
    float pdbVoltageFiltered = PDB.getFilteredVoltage();
    bool failsafeStateFiltered = Failsafe.getFilteredState();
    float thruster1And2VoltageFiltered = Thruster1And2.getFilteredVoltage();
    float thruster3And4VoltageFiltered = Thruster3And4.getFilteredVoltage();
    
    // Relay Logic (START) ==========
    // If the Precharge for Xavier is almost fully charged, activate the relay to let Xavier get power
    if (xavierVoltageFiltered >= THRESHOLD_XAVIER) {
        digitalWrite(RELAY_XAVIER, HIGH);
    }
    else {
        digitalWrite(RELAY_XAVIER, LOW);
    }

    // If the Precharge for PDB is almost fully charged, activate the relay to let PDB get power
    if (pdbVoltageFiltered > THRESHOLD_PDB) {
        digitalWrite(RELAY_PDB, HIGH);
    }
    else {
        digitalWrite(RELAY_PDB, LOW);
    }

    // Failsafe and Thrusters Relay/Precharge logic
    /*
    * For the Failsafe and by extent the Thrusters, its a bit more involved
    * Failsafe dictates in itself if the Thruster Precharge gets to be charged
    * This means that if Failsafe is triggered and goes DOWN/LOW
    * The Thruster Precharge loses power for safety
    * And thus there is no point in checking Thruster Precharge if the Failsafe is DOWN/LOW
    * Only when Failsafe is ACTIVE/HIGH can Thruster Precharge start charging
    * ANd only then is it necessary to check when the Thruster Precharge is almost full to let Thrusters have power
    */
    if (failsafeStateFiltered == THRESHOLD_FAILSAFE) {
        // Activate Failsafe relay, allowing Thruster Precharge system to start charging
        digitalWrite(RELAY_FAILSAFE, HIGH);

        // Only now can we check for Thruster Precharge and relay logic
        // Precharge for thruster 1 and 2, if almost charged, activate relay to give power to thruster 1 and 2
        if (thruster1And2VoltageFiltered > THRESHOLD_THRUSTER_1_AND_2) {
            digitalWrite(RELAY_THRUSTERS_1_AND_2, HIGH);
        }
        else {
            digitalWrite(RELAY_THRUSTERS_1_AND_2, LOW);
        }

        // Precharge for thruster 3 and 4, if almost charged, activate relay to give power to thruster 3 and 4
        if (thruster3And4VoltageFiltered > THRESHOLD_THRUSTER_3_AND_4) {
            digitalWrite(RELAY_THRUSTERS_3_AND_4, HIGH);
        }
        else {
            digitalWrite(RELAY_THRUSTERS_3_AND_4, LOW);
        }
    }
    else {
        digitalWrite(RELAY_FAILSAFE, LOW);

        // Since Failsafe is triggered, the Thrusters Relays should also go down just in case
        digitalWrite(RELAY_THRUSTERS_1_AND_2, LOW);
        digitalWrite(RELAY_THRUSTERS_3_AND_4, LOW);
    }
    // Relay Logic (STOP) ==========

    // A small delay to avoid rapid toggling
    delayMicroseconds(100);
}
// Main Loop (STOP) ==================================================
