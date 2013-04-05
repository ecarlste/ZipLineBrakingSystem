
#include <ADXL345.h>
#include <Servo.h>
#include <Wire.h>


// Digital Pin Mapping
#define SECURE_PIN 11
#define SERVO_PIN 9


// Analog Pin Mapping
#define BATTERY_PIN 0


// Temperature Sensor Definitions
#define TMP36_VOUT 1
#define TMP36_MILLIVOLTS_PER_DEGREE_C 10


// Brake Servo Definitions
#define BRAKES_OFF 0
#define BRAKES_HOLD 165
#define BRAKES_FULL 175
Servo brakeServo;


// Accelerometer Definitions
#define ADXL345SCL_PIN 5
#define ADXL345SDA_PIN 4
ADXL345 adxl;


// LED Definitions
#define LED0 7
#define LED1 8
#define LED2 12
#define LED3 13
#define LED_OFF 0
#define LED_ON 1

// Interrupt Definitions
#define RETURN_IRQ 0


void setup() {
  // Set initial pin modes
  pinMode(SECURE_PIN, INPUT);

  // set up brake servo
  brakeServo.attach(SERVO_PIN);
  
  // initialize the ADXL345 accelerometer
  adxl.powerOn();
  
  // Set up interrupts
  attachInterrupt(RETURN_IRQ, returnToStart, RISING);
}


void loop() {
}


void setBrakeServoAngle(int angle) {
  brakeServo.write(angle);
}


int getBatteryLevel() {
  int value = analogRead(BATTERY_PIN);
  return 100 * value / 1023;
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


void setLED(int pin, int value) {
  if (value == LED_ON) {
    digitalWrite(pin, HIGH);
  }
  else if (value == LED_OFF) {
    digitalWrite(pin, LOW);
  }
}


int getTemperature() {
  int voltage = analogRead(TMP36_VOUT);
  int temp = voltage * 1000 / TMP36_MILLIVOLTS_PER_DEGREE_C;
  return temp;
}


void returnToStart() {
}


void getAcceleration(int *x, int *y, int *z) {
  adxl.readAccel(x, y, z);
}
