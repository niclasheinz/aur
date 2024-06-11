/* 
#===============================================================================
#
#          FILE:  Arduino-with-remote-control_obstacle-detection.ino
#         USAGE:  Only compatible with Arduino IDE
# ARDUINO MODEL:  Arduino Uno
#
#   DESCRIPTION:  My goal is to build and program a robot that can be controlled
                  by a remote control. I am also working on an all-round obstacle
                  detection system.
#
#  REQUIREMENTS:  Arduino, Arduino-Desktopapp, IRremote 4.3.1 by shirriff
#          BUGS:  ---
#         NOTES:  I'm using version 4 of the IRremote Libary. With a different version, parts may not work.
#        AUTHOR:  Niclas Heinz
#        GITLAB:  www.gitlab.com/niclasheinz/aur
#       COMPANY:  - 
#       VERSION:  5.0
#      REVISION:  ---
#===============================================================================
 */

#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11
// Pins for the obstacle detectors
int TRIGGER_front = 4;
int TRIGGER_right = 12;
int TRIGGER_left = 7;
int TRIGGER_back = 1;
int ECHO_front = 3; 
int ECHO_right = 13;
int ECHO_left = 8;
int ECHO_back = 2;
// Variable for saving the distance
long Distance_front = 0; 
long Distance_right = 0; 
long Distance_left = 0;
long Distance_back = 0;
void setup() {
// Activate pins 
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(6, OUTPUT);
pinMode(6, OUTPUT);
pinMode(4, OUTPUT);  
pinMode(TRIGGER_front, OUTPUT);
pinMode(ECHO_front, INPUT);
pinMode(TRIGGER_right,  OUTPUT);
pinMode(ECHO_right, INPUT);
// Serial Monitor
Serial.begin(9600);        // Start serial communication to receive data using serial monitor
IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Start the receiver
}

// manoeuvre that the arduino script supports

void drive_forwards() { // driving forwards
       Serial.println("Drive forwards (2)");
        digitalWrite(6, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(9, LOW);
        analogWrite(10, 230);
        digitalWrite(2, HIGH);
}

void drive_backwards() { // driving backwards
        Serial.println("Drive backwards (3)");
        digitalWrite(6, LOW);
        digitalWrite(10, LOW);
        digitalWrite(2, LOW);
        analogWrite(6, 70);
        analogWrite(10, 70);
        digitalWrite(6, LOW);
        digitalWrite(10, LOW);
        delay(500);
        analogWrite(9, 150);
        analogWrite(5, 150);
        delay(500);
        digitalWrite(9, HIGH);
        digitalWrite(5, HIGH);
}

void stop_all() { //stop all motors
        Serial.println("stop all (On/Off)");
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
}

void turn_left() { // turning left
        Serial.println("Turn left (9)");
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(2, LOW);
        digitalWrite(9, HIGH);
        digitalWrite(6, LOW);
        delay(250);
        digitalWrite(9, LOW);
}

void turn_right() { //turning right
        Serial.println("Turn right (4)");
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(2, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(10, LOW);
        delay(250);
        digitalWrite(6, LOW);
}

void bypass_left() { // function for bypass objects from left side
    Serial.println("Bypass left")
}

void bypass_right() { // function for bypass objects from right side
    Serial.println("Bypass right")
}

void loop() {

  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, DEC);  // Print "old" raw data
    //IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    //IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case 4077715200:  //Drive forwards
        drive_forwards();
        break;
      case 3877175040:  // drive backwards
        drive_backwards();
        break;
      case 2707357440:  // turn right
        turn_right();
        break;
      case 4144561920:  // turn left
        turn_left();
        break;
      case 3125149440:  // force stop all motors
        stop_all();
        break;
    }
  }

  IrReceiver.resume();  // Enable receiving of the next value

//////////////// Obstacle Detector front  ////////////////////
digitalWrite(TRIGGER_front, LOW);
 // delay(5);

  // transmit signal for 10 microseconds, afterwards turn off
  digitalWrite(TRIGGER_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_front, LOW);

  // pulseIn -> time measurement, until receiving a signal
  long time_front = pulseIn(ECHO_front, HIGH);

  // calculate distance in cm
  // time/2 -> only one track
  Distance_front = (time_front / 2) * 0.03432;
  delay(50);

  // display only distance < 100
  if (Distance_front < 1000) 
  {
    // display measurement data
    Serial.print("Distance Front in cm: ");
    Serial.println(Distance_front);
  }
  if (Distance_front < 40) {
    Serial.print("unter 40");
        stop_all();
        delay(1000);
        drive_backwards();
        delay(2000);
        stop_all();
        delay(1000);
}
delay(100);
//////////////// Obstacle Detector right  ////////////////////
digitalWrite(TRIGGER_right, LOW);
  delay(5);

  // transmit signal for 10 microseconds, afterwards turn off
  digitalWrite(TRIGGER_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_right, LOW);

  // pulseIn -> time measurement, until receiving a signal
  long time_right = pulseIn(ECHO_right, HIGH);

  // calculate distance in cm
  // time/2 -> only one track
  Distance_right = (time_right / 2) * 0.03432;
  delay(50);

  // display only distance < 100
  if (Distance_right < 1000) 
  {
    // display measurement data
    Serial.print("Distance from right in cm: ");
    Serial.println(Distance_right);
  }
  if (Distance_right < 40) {
    Serial.print("right");
        stop_all(); // stop all
        delay(1000);
        // drive backwards
        drive_backwards();
        delay(2000);
        stop_all();
        delay(1000);
}
//////////////// Obstacle Detector left  ////////////////////
digitalWrite(TRIGGER_left, LOW);
  delay(5);

  // transmit signal for 10 microseconds, afterwards turn off
  digitalWrite(TRIGGER_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_left, LOW);

  // pulseIn -> time measurement, until receiving a signal
  long time_left = pulseIn(ECHO_left, HIGH);

  // calculate distance in cm
  // time/2 -> only one track
  Distance_left = (time_left / 2) * 0.03432;
  delay(5);

  // display only distance < 100
  if (Distance_left < 1000) 
  {
    // display measurement data
    Serial.print("Distance from left in cm: ");
    Serial.println(Distance_left);
  }
  if (Distance_left < 60) {
    Serial.print("right");
        stop_all();
        delay(1000);
        drive_backwards();
        delay(2000);
        stop_all();
        delay(1000);
}

//////////////// Obstacle Detector back  ////////////////////
digitalWrite(TRIGGER_back, LOW);
  delay(5);

  // transmit signal for 10 microseconds, afterwards turn off
  digitalWrite(TRIGGER_back, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_back, LOW);

  // pulseIn -> time measurement, until receiving a signal
  long time_back = pulseIn(ECHO_back, HIGH);

  // calculate distance in cm
  // time/2 -> only one track
  Distance_back = (time_left / 2) * 0.03432;
  delay(5);

  // display only distance < 100
  if (Distance_back < 1000) 
  {
    // display measurement data
    Serial.print("Distance from back in cm: ");
    Serial.println(Distance_back);
  }
  if (Distance_back < 60) {
        Serial.print("Near an obstacle behind the arduino")
        stop_all();
        delay(1000);
        drive_backwards();
        delay(2000);
        stop_all();
        delay(1000);
}

}
