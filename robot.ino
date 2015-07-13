#include "ByteBuffer.h"
#include "SoftwareSerial.h"
#include "sabertooth.h"
#include "NewPing.h"

static const char NEWLINE = 10;
static const double GLOBAL_ACCELERATION = 0.1;

// Sabertooth SoftwareSerial pins
static const int rxPin = 2;
static const int txPin = 3;

// Ultrasonic sensor
static const int US_TRIGGER_PIN = 4;
static const int US_ECHO_PIN = 5;
static const int US_MAX_DISTANCE = 200;
static const int US_SOS_CM = 10;
static const unsigned long US_PING_INTERVAL = 50;

// Initialisations

// Serial command input
char latestByte;
int bytesAvailable = 0;
ByteBuffer commandBuffer;
char command[65];

// motor controller
Sabertooth * sabertooth;

// Ultrasonic
NewPing sonar(US_TRIGGER_PIN, US_ECHO_PIN, US_MAX_DISTANCE);
int us_distance;
unsigned long pingTimer;

void setup() {
  if(Serial)
  {
    Serial.begin(9600);
    Serial.println("Initialising...");
    sabertooth = new Sabertooth(rxPin, txPin, 9600);
    sabertooth->motors[0].setBounds(127, 64, 1);
    sabertooth->motors[1].setBounds(128, 191, 255);
    sabertooth->motors[0].setAcceleration(GLOBAL_ACCELERATION);
    sabertooth->motors[1].setAcceleration(GLOBAL_ACCELERATION);
    sabertooth->halt(); // Initialise stopped
    pingTimer = millis() + 100; // first ping time
    Serial.println("Initialised.");
  }
}

void echoCheck() {
  if(sonar.check_timer()) {
    us_distance = sonar.ping_result / US_ROUNDTRIP_CM;

    Serial.print(millis());
    Serial.print(": Ultrasonic : ");
    Serial.print(us_distance);
    Serial.println("cm");
    
    if(us_distance <= US_SOS_CM) {
      Serial.println("SOS");
      sabertooth->stop();
    }
  }
}

void loop() {

  if(millis() >= pingTimer) {
    sonar.timer_stop();
    pingTimer = millis() + US_PING_INTERVAL;
    sonar.ping_timer(echoCheck);
  }
  
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
