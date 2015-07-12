#ifndef Sabertooth_h
#define Sabertooth_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class Sabertooth
{
  public:
    Sabertooth(int rxPin, int txPin, int baud);
    ~Sabertooth();
    void M1Forward();
    void M1Stop();
    void M1Reverse();
    void M2Forward();
    void M2Stop();
    void M2Reverse();
  private:
    SoftwareSerial * serial;
};

#endif

