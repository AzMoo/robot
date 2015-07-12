#ifndef Sabertooth_h
#define Sabertooth_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class Motor
{
  public:
    Motor();
    void accelerateTo(int target, int duration);
    void setPower(int power);
    void setAcceleration(double accel);
    void setTargetPower(int power);
    int getCurrentPower();
  private:
    int currentPower;
    int targetPower;
    unsigned int lastUpdate;
    double acceleration;
};

class Sabertooth
{
  public:
    Sabertooth(int rxPin, int txPin, int baud);
    ~Sabertooth();
    void update();
    Motor motors[2];
  private:
    int nextUpdate;
    SoftwareSerial * serial;
};

#endif
