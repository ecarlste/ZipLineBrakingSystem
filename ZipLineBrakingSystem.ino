
#include <Servo.h>


// Digital Pin Mapping
const int LED0 = 0;
const int LED1 = 1;
const int LED2 = 4;
const int LED3 = 5;
const int LED4 = 6;
const int LED5 = 7;
const int LED6 = 8;
const int LED7 = 10;

const int returnPin = 2;
const int securePin = 11;
const int servoPin = 9;


// Analog Pin Mapping
const int ADXL345SCL = 5;
const int ADXL345SDA = 4;

const int batteryPin = 0;


// Servo Definitions
Servo brakeServo;


void setup() {
  brakeServo.attach(servoPin);
}


void loop() {
}


void setBrakeServoAngle(int angle) {
  brakeServo.write(angle);
}
