#ifndef Sabertooth_h
#define Sabertooth_h

#include "Arduino.h"
#include "SoftwareSerial.h"

struct Bounds {
  int ahead;
  int neutral;
  int reverse;
};

class Motor
{
  public:
    Motor();
    void accelerateTo(int target, int duration);
    void setPower(int power);
    void setAcceleration(double accel);
    void setTargetPower(int power);
    void setBounds(int ahead, int neutral, int reverse);
    void setFullAhead();
    void setNeutral();
    void setFullReverse();
    void halt();
    int getCurrentPower();
  private:
    Bounds bounds;
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
    void forward();
    void reverse();
    void stop();
    void halt();
    void turnLeft();
    void turnRight();
  private:
    int nextUpdate;
    SoftwareSerial * serial;
};

#endif
