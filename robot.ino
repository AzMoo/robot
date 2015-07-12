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
    Serial.println("Initialising...");
    sabertooth->motors[0].setBounds(127, 64, 1);
    sabertooth->motors[1].setBounds(128, 191, 255);
    sabertooth->motors[0].setAcceleration(GLOBAL_ACCELERATION);
    sabertooth->motors[1].setAcceleration(GLOBAL_ACCELERATION);
    sabertooth->halt(); // Initialise stopped
    Serial.println("Initialised.");
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
      if(strcmp(command, "AllAhead") == 0) {
        Serial.println("Received AllAhead");
        sabertooth->forward();
      } else if(strcmp(command, "AllStop") == 0) {
        Serial.println("Received AllStop");
        sabertooth->stop();
      } else if(strcmp(command, "AllReverse") == 0) {
        Serial.println("Received AllReverse");
        sabertooth->reverse();
      } else if(strcmp(command, "HardLeft") == 0) {
        Serial.println("Received HardLeft");
        sabertooth->turnLeft();
      } else if(strcmp(command, "HardRight") == 0) {
        Serial.println("Received HardRight");
        sabertooth->turnRight();
      } else if(strcmp(command, "SOS") == 0) {
        Serial.println("Received SOS");
        sabertooth->halt();
      }
      commandBuffer.empty();
    } else {
      commandBuffer.push(latestByte);
    }
  }

  sabertooth->update();
}
