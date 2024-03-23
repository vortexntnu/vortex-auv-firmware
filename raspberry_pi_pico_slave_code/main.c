#include <Servo.h>
#include <Wire.h>
#include <Arduino.h>

#define ESC_PIN1  18
#define ESC_PIN2  19
#define ESC_PIN3  20
#define ESC_PIN4  21
#define ESC_PIN5  22
#define ESC_PIN6  26
#define ESC_PIN7  27
#define ESC_PIN8  28

#define ARMING_PWM    1500
#define STARTUP_DELAY 1500
#define I2C_ADDRESS   0x21

bool status = 1;

uint16_t PWM_values[8];

Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;
Servo ESC5;
Servo ESC6;
Servo ESC7;
Servo ESC8;

bool IS_HIGH_BYTE = 1;

void arm_thrusters();
void drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4, int PWM_ESC5, int PWM_ESC6, int PWM_ESC7, int PWM_ESC8);
void receiveMessage(int bytes);


void setup() {
  Serial.begin(115200);

  delay(5000);
  Serial.println("Configuring ESCs...");
  ESC1.attach(ESC_PIN1);
  ESC2.attach(ESC_PIN2);
  ESC3.attach(ESC_PIN3);
  ESC4.attach(ESC_PIN4);
  ESC5.attach(ESC_PIN5);
  ESC6.attach(ESC_PIN6);
  ESC7.attach(ESC_PIN7);
  ESC8.attach(ESC_PIN8);

  arm_thrusters();

  Serial.println("Cig break brb...");
  delay(STARTUP_DELAY);

  Serial.println("Setting up I2C communication...");
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveMessage);
  //Wire.onRequest(sendMessage);

  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  pinMode(25, OUTPUT);

  for(int i=0; i < 5; i++)
  {
    digitalWrite(25, HIGH);
    delay(256);
    digitalWrite(25, LOW);
    delay(250);
  }
}

void loop() {

}

void drive_thrusters(int PWM_ESC1, int PWM_ESC2, int PWM_ESC3, int PWM_ESC4, int PWM_ESC5, int PWM_ESC6, int PWM_ESC7, int PWM_ESC8) {
  ESC1.writeMicroseconds(PWM_ESC1);
  ESC2.writeMicroseconds(PWM_ESC2);
  ESC3.writeMicroseconds(PWM_ESC3);
  ESC4.writeMicroseconds(PWM_ESC4);
  ESC5.writeMicroseconds(PWM_ESC5);
  ESC6.writeMicroseconds(PWM_ESC6);
  ESC7.writeMicroseconds(PWM_ESC7);
  ESC8.writeMicroseconds(PWM_ESC8);
}

void arm_thrusters() {
  ESC1.writeMicroseconds(ARMING_PWM);
  ESC2.writeMicroseconds(ARMING_PWM);
  ESC3.writeMicroseconds(ARMING_PWM);
  ESC4.writeMicroseconds(ARMING_PWM);
  ESC5.writeMicroseconds(ARMING_PWM);
  ESC6.writeMicroseconds(ARMING_PWM);
  ESC7.writeMicroseconds(ARMING_PWM);
  ESC8.writeMicroseconds(ARMING_PWM);
}


void receiveMessage(int bytes)
{
  Wire.write();

  for(int i=0; i<16; i++)
  {
    int msb = Wire.read();
    int lsb = Wire.read();

    PWM_values[i] = (msb << 8);
    PWM_values[i] |= lsb;

  }

  drive_thrusters(PWM_values[0], PWM_values[1], PWM_values[2], PWM_values[3], PWM_values[4], PWM_values[5], PWM_values[6], PWM_values[7]);
    
  // Print the values for debugging
  Serial.print("PWM values: ");
  for (int j = 0; j < 8; j++) {
    Serial.print(PWM_values[j]);
    Serial.print(" ");
  }
  Serial.println();
}