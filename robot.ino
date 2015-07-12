#include "ByteBuffer.h"
#include "SoftwareSerial.h"
#include "sabertooth.h"

const char NEWLINE = 10;
char latestByte;
int bytesAvailable = 0;
ByteBuffer commandBuffer;
char command[65];
Sabertooth * sabertooth;
int rxPin = 2;
int txPin = 3;

void setup() {
  // put your setup code here, to run once:
  if(Serial)
  {
    Serial.begin(9600);
    sabertooth = new Sabertooth(rxPin, txPin, 9600);
    sabertooth->M1Stop();
    sabertooth->M2Stop();
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
      if(strcmp(command, "M1F") == 0) {
        sabertooth->M1Forward();
      } else if(strcmp(command, "M1S") == 0) {
        sabertooth->M1Stop();
      } else if(strcmp(command, "M1R") == 0) {
        sabertooth->M1Reverse();
      } else if(strcmp(command, "M2F") == 0) {
        sabertooth->M2Forward();
      } else if(strcmp(command, "M2S") == 0) {
        sabertooth->M2Stop();
      } else if(strcmp(command, "M2R") == 0) {
        sabertooth->M2Reverse();
      }
      commandBuffer.empty();
    } else {
      commandBuffer.push(latestByte);
    }
  }
}
