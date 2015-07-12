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

void Motor::setBounds(int ahead, int neutral, int reverse) {
  bounds.ahead = ahead;
  bounds.neutral = neutral;
  bounds.reverse = reverse;
}

void Motor::setFullAhead() {
  setTargetPower(bounds.ahead);
}

void Motor::setFullReverse() {
  setTargetPower(bounds.reverse);
}

void Motor::setNeutral() {
  setTargetPower(bounds.neutral);
}

void Motor::halt() {
  setPower(bounds.neutral);
}

int Motor::getCurrentPower() {
  if(acceleration != 0 && currentPower != targetPower) {
    int timePassed = millis() - lastUpdate;
    
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

    serial->write(motor0Power);
    serial->write(motor1Power);

    nextUpdate = currentTime + 100;
  }
}

void Sabertooth::forward() {
  motors[0].setFullAhead();
  motors[1].setFullAhead();
}

void Sabertooth::reverse() {
  motors[0].setFullReverse();
  motors[1].setFullReverse();
}

void Sabertooth::stop() {
  motors[0].setNeutral();
  motors[1].setNeutral();
}

void Sabertooth::turnLeft() {
  motors[0].setFullReverse();
  motors[1].setFullAhead();
}

void Sabertooth::turnRight() {
  motors[0].setFullAhead();
  motors[1].setFullReverse();
}

void Sabertooth::halt() {
  motors[0].halt();
  motors[1].halt();
}

