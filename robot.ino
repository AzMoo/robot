#include "ByteBuffer.h"
#include "SoftwareSerial.h"
#include "sabertooth.h"

const char NEWLINE = 10;
const double GLOBAL_ACCELERATION = 0.1;
char latestByte;
int bytesAvailable = 0;
ByteBuffer commandBuffer;
char command[65];
Sabertooth * sabertooth;
int rxPin = 2;
int txPin = 3;

void setup() {
  if(Serial)
  {
    Serial.begin(9600);
    sabertooth = new Sabertooth(rxPin, txPin, 9600);
    Serial.println("Initialising");
    sabertooth->motors[0].setPower(64);
    sabertooth->motors[1].setPower(191);
  }
}

void loop() {
  /* 
   *  Read until newline
   *  Execute command in buffer on Sabertooth
   *  Clear buffer for next command
   */
  if(Serial.available()) {
    latestByte = Serial.read();

    if(latestByte == NEWLINE) {
      commandBuffer.asString(command);
      if(strcmp(command, "M0F") == 0) {
        // Accelerate to Full Speed at 0.05units/ms
        Serial.println("Accelerating M0");
        sabertooth->motors[0].setTargetPower(127);
        sabertooth->motors[0].setAcceleration(GLOBAL_ACCELERATION);
      } else if(strcmp(command, "M0S") == 0) {
        // Take 1 second to accelerate motor 0 to full stop
        Serial.println("Stopping M0");
        sabertooth->motors[0].setTargetPower(64);
        sabertooth->motors[0].setAcceleration(GLOBAL_ACCELERATION);
      } else if(strcmp(command, "M1F") == 0) {
        // Accelerate to Full Speed at 0.05units/ms
        Serial.println("Accelerating M1");
        sabertooth->motors[1].setTargetPower(128);
        sabertooth->motors[1].setAcceleration(GLOBAL_ACCELERATION);
      } else if(strcmp(command, "M1S") == 0) {
        // Take 1 second to accelerate motor 0 to full stop
        Serial.println("Stopping M1");
        sabertooth->motors[1].setTargetPower(191);
        sabertooth->motors[1].setAcceleration(GLOBAL_ACCELERATION);
      }
      commandBuffer.empty();
    } else {
      commandBuffer.push(latestByte);
    }
  }

  sabertooth->update();
}
