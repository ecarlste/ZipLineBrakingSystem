
#include <ADXL345.h>
#include <Servo.h>
#include <Wire.h>


// Digital Pin Mapping
#define SECURE_PIN 11
#define SERVO_PIN  9


// Battery Definitions
#define BATTERY_PIN       0
#define BATTERY_LEVEL_MIN 25

// Temperature Sensor Definitions
#define TMP36_VOUT                    1
#define TMP36_MILLIVOLTS_PER_DEGREE_C 10
#define OPERATING_TEMP_MAX            70


// Brake Servo Definitions
#define BRAKES_OFF  0
#define BRAKES_HOLD 165
#define BRAKES_FULL 175

Servo brakeServo;


// Accelerometer Definitions
#define ADXL345SCL_PIN 5
#define ADXL345SDA_PIN 4

ADXL345 adxl;


// LED Definitions
#define LED0    7
#define LED1    8
#define LED2    12
#define LED3    13
#define LED_OFF 0
#define LED_ON  1


// Interrupt Definitions
#define RETURN_IRQ 0


// System Operating Modes
#define MODE_AWAITING_RETURN 0
#define MODE_RETURNING       1
#define MODE_AWAITING_IMPACT 2
#define MODE_BRAKING         3

int mode;


// System Status Definitions
#define BATTERY_OK           1
#define ACCELEROMETER_OK     2
#define CASE_SECURE_OK       4
#define TEMP_OK              8
#define SYSTEM_OK            15

#define BATTERY_OK_LED       LED0
#define ACCELEROMETER_OK_LED LED1
#define CASE_SECURE_OK_LED   LED2
#define TEMP_OK_LED          LED3


void setup() {
  // Set initial pin modes
  pinMode(SECURE_PIN, INPUT);

  // set up brake servo
  brakeServo.attach(SERVO_PIN);
  
  // initialize the ADXL345 accelerometer
  adxl.powerOn();
  
  // Set up interrupts
  attachInterrupt(RETURN_IRQ, setModeReturning, RISING);
  
  mode = MODE_AWAITING_RETURN;
}


void loop() {
  switch (mode) {
    case MODE_AWAITING_RETURN:
      break;
    case MODE_RETURNING:
      returnToStart();
      break;
    case MODE_AWAITING_IMPACT:
      waitForImpact();
      break;
    case MODE_BRAKING:
      slowToStop();
      break;
    default:
      break;
  }
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


void setModeReturning() {
  mode = MODE_RETURNING;
}


void returnToStart() {
  // check the system status to ensure ready to return
  int status = getSystemStatus();
  updateLEDs(status);
  
  // start return trip
  
  // stop moving when distance reached
  
  // apply hold brake force
  
  // set mode to waiting for impact
}


void waitForImpact() {
  // wait for the total acceleration to be greater than 1.5g
  
  // set mode to braking
}


void slowToStop() {
  // determine velocity using acceleration and Vo = 0
  
  // determine the acceleration needed to slow to 0 m/s in the given distance
  
  // determine braking force needed to achieve the desired acceleration
  
  // once velocity is near 0, or acceleration is near 1g, set mode to return waiting
}


int getSystemStatus() {
  int systemStatus = 0;
  
  // check battery status
  if (getBatteryLevel() > BATTERY_LEVEL_MIN) {
    systemStatus |= BATTERY_OK;
  }
  
  // check that case is secured
  if (isCaseSecure()) {
    systemStatus |= CASE_SECURE_OK;
  }
  
  // check temperature
  int temperature = getTemperature();
  if (temperature < OPERATING_TEMP_MAX) {
    systemStatus |= TEMP_OK;
  }
  
  // check accelerometer
  if (adxl.status == ADXL345_OK) {
    systemStatus |= ACCELEROMETER_OK;
  }
  
  return systemStatus;
}


void updateLEDs(int status) {
  if ((BATTERY_OK & status) == 0) {
    digitalWrite(BATTERY_OK_LED, LOW);
  }
  else {
    digitalWrite(BATTERY_OK_LED, HIGH);
  }
  
  if ((ACCELEROMETER_OK & status) == 0) {
    digitalWrite(ACCELEROMETER_OK_LED, LOW);
  }
  else {
    digitalWrite(ACCELEROMETER_OK_LED, HIGH);
  }
  
  if ((CASE_SECURE_OK & status) == 0) {
    digitalWrite(CASE_SECURE_OK_LED, LOW);
  }
  else {
    digitalWrite(CASE_SECURE_OK_LED, HIGH);
  }
  
  if ((TEMP_OK & status) == 0) {
    digitalWrite(TEMP_OK_LED, LOW);
  }
  else {
    digitalWrite(TEMP_OK_LED, HIGH);
  }
}


void getAcceleration(int *x, int *y, int *z) {
  adxl.readAccel(x, y, z);
}
