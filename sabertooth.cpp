#include "Arduino.h"
#include "sabertooth.h"
#include "SoftwareSerial.h"


Sabertooth::Sabertooth(int rxPin, int txPin, int baud) {
  serial = new SoftwareSerial(rxPin, txPin);
  serial->begin(baud);
}

Sabertooth::~Sabertooth() {
  delete serial;
}

void Sabertooth::M1Forward()
{
  Serial.println("Motor 1 Forward");
  serial->write(127);
}

void Sabertooth::M1Stop()
{
  Serial.println("Motor 1 Stop");
  serial->write(64);
}

void Sabertooth::M1Reverse()
{
  Serial.println("Motor 1 Reverse");
  serial->write(1);
}

/*
 * For some reason M2's values are all inverted. The documentation 
 * says M2 should range from full reverse at 128 to 
 * full forward at 255, but in reality it's doing the opposite.
 * 
 * I imagine this is why 191 is the stop point instead of 192.
 */

void Sabertooth::M2Forward()
{
  Serial.println("Motor 2 Forward");
  serial->write(128);
}

void Sabertooth::M2Stop()
{
  // This should be 192 but 192 gives me voltage
  // and 191 does not.
  Serial.println("Motor 2 Stop");
  serial->write(191);
}

void Sabertooth::M2Reverse()
{
  Serial.println("Motor 2 Reverse");
  serial->write(255);
}

