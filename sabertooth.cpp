#include "Arduino.h"
#include "sabertooth.h"
#include "SoftwareSerial.h"

Motor::Motor() {
  lastUpdate = millis();
  acceleration = 0;
  currentPower = 0;
}

void Motor::setTargetPower(int target) {
  targetPower = target;
}

void Motor::setAcceleration(double accel) {
  acceleration = accel;
}

int Motor::getCurrentPower() {
  if(acceleration != 0 && currentPower != targetPower) {
    int timePassed = millis() - lastUpdate;
    //currentPower = currentPower + (timePassed * acceleration);

    Serial.print("Time Passed: ");
    Serial.println(timePassed);

    if(currentPower > targetPower) {
      currentPower = currentPower - (timePassed * acceleration);
      
      if(targetPower > currentPower) {
        currentPower = targetPower;
      }
    } else {
      currentPower = currentPower + (timePassed * acceleration);

      if(targetPower < currentPower) {
        currentPower = targetPower;
      }
    }
  }

  lastUpdate = millis();

  return currentPower;
}

void Motor::setPower(int power) {
  currentPower = power;
  targetPower = power;
}

Sabertooth::Sabertooth(int rxPin, int txPin, int baud) {
  serial = new SoftwareSerial(rxPin, txPin);
  serial->begin(baud);
  nextUpdate = 0;
}

Sabertooth::~Sabertooth() {
  delete serial;
}

void Sabertooth::update() {

  int currentTime = millis();
  
  if(nextUpdate <= currentTime) {
  
    int motor0Power = motors[0].getCurrentPower();
    int motor1Power = motors[1].getCurrentPower();

    Serial.print("Motor 0: ");
    Serial.print(motor0Power);
    Serial.print("\tMotor 1: ");
    Serial.println(motor1Power);
  
    serial->write(motor0Power);
    serial->write(motor1Power);

    nextUpdate = currentTime + 100;
  }
}

