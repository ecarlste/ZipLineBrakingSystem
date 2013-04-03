
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
#define NO_BRAKES 0
#define FULL_BRAKES 165
Servo brakeServo;

void setup() {
  // Set initial pin modes
  pinMode(SECURE_PIN, INPUT);

  // set up brake servo
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


int isCaseSecure() {
  int value = digitalRead(SECURE_PIN);
//------------------------------------------------------------------------------
  /*
  Here we expect that if the case is secured shut that the circuit attached to
  the SECURE_PIN will show a voltage of 3V or more. If it is then we should
  return true. Otherwise the case is not secured, and we should return false.
   */
  if (value == HIGH) {
    return 1;
  } 
  else {
    return 0;
  }
}

