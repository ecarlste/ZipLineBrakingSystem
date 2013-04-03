
#include <Servo.h>


// Digital Pin Mapping
#define LED0 0
#define LED1 1
#define LED2 4
#define LED3 5
#define LED4 6
#define LED5 7
#define LED6 8
#define LED7 10

#define RETURN_PIN 2
#define SECURE_PIN 11
#define SERVO_PIN 9


// Analog Pin Mapping
#define ADXL345SCL 5
#define ADXL345SDA 4

#define BATTERY_PIN 0


// Brake Servo Definitions
Servo brakeServo;
#define NO_BRAKES 0
#define FULL_BRAKES 165

void setup() {
  brakeServo.attach(SERVO_PIN);
}


void loop() {
}


void setBrakeServoAngle(int angle) {
  brakeServo.write(angle);
}


int getBatteryLevel() {
  int value = analogRead(BATTERY_PIN);
  return value / 1023;
}

