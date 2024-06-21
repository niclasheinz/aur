/* 
#===============================================================================
#
#          FILE:  Arduino-with-remote-control_obstacle-detection.ino
#         USAGE:  Only compatible with Arduino Uno
# ARDUINO MODEL:  Arduino Uno
#
#   DESCRIPTION:  My goal is to build and program a robot that can be controlled
                  by a remote control. I'm also working on an all-round obstacle
                  detection system with a easy bypass functionality. 
#
#  REQUIREMENTS:  Arduino Uno, Arduino IDE, IRremote 4.3.1 by shirriff and this script of course :)
#          BUGS:  ---
#         NOTES:  I'm using version 4 of the IRremote Libary. With a different version, parts may not work.
#        AUTHOR:  Niclas Heinz
#        GITLAB:  www.gitlab.com/niclasheinz/aur
#       COMPANY:  - 
#       VERSION:  6.3
# LATEST COMMIT: 20.06.2024
#===============================================================================
 */

#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11

// Pins for the obstacle detectors
int TRIGGER_front = 4;
int TRIGGER_back = 7;

//int TRIGGER_back = 1;
int ECHO_front = 3; 
int ECHO_back = 8;


// Variable for saving the distance
long Distance_front = 0; 
long Distance_back = 0;

// Variables for the motors
int mo_re_1 = 9;
int mo_re_2 = 10;
int mo_li_1 = 6;
int mo_li_2 = 7;
int obstacle_detector_left_PIN = 12;
void setup() {
// Activate pins 
pinMode(2, INPUT); // distance sensor right
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(6, OUTPUT);
pinMode(12, INPUT); // distance sensor left
//pinMode(obstacle_sensor_right, INPUT);
pinMode(TRIGGER_front, OUTPUT);
pinMode(ECHO_front, INPUT);
pinMode(TRIGGER_back,  OUTPUT);
pinMode(ECHO_back, INPUT);
// Serial Monitor
Serial.begin(9600);        // Start serial communication to receive data using serial monitor
IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Start the receiver
}

// manoeuvre that the arduino script supports //
void drive_forwards() { // driving forwards
       Serial.println("Drive forwards (2)");
        digitalWrite(6, HIGH);
        analogWrite(10, 230);
//      digitalWrite(10, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(9, LOW);
}

void drive_forwards_bypass() {
    analogWrite(10, 130);
    analogWrite(6, 130);
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

void turn_right() { //turing right
        Serial.println("Drehung nach rechts (4)");
        digitalWrite(8, LOW);
        digitalWrite(mo_re_1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(mo_re_2, LOW);
        delay(250);
        digitalWrite(mo_li_2, LOW);
}

void turn_back() { //turning back
        Serial.println("Turn back (4)");
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(2, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(10, LOW);
        delay(250);
        digitalWrite(6, LOW);
}

void bypass_left() { // function for bypass objects from left side
    Serial.println("Bypass left");
    // 1. reduce speed
    drive_forwardsbypass();
    delay(1000);
    drive_forwardsbypassstop();
    turn_right();

    // 2. turn back with analogWrite
    // 3. drive straight
    drive_forwards_bypass();
    // 4. turn left
    // 5. drive straight
    // 6. turn left
}

void stop_back() {

}
void drive_forwardsbypass() {
    analogWrite(10, 230);
    analogWrite(6, 130);
}
void drive_forwardsbypassstop() {
    analogWrite(10, 0);
    analogWrite(6, 0);
}

void bypass_right() { // function for bypass objects from right side
    Serial.println("Bypass right");
    // 1. reduce speed
    //analogWrite()
    // 2. turn left // using analogWrite
    // 3. drive straight
    // 4. turn right
    // 5. drive traight
    // 6. turn right
}

void force_stop(){ // if distance to one of the sensors is lower than 30 -> force stop
  if (Distance_front < 30 || Distance_back < 30) {
    Serial.println("Executing force-stop in 1s");
    stop_all();
  }
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


delay(100);
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
        Serial.print("Obstacle detected front side");
        stop_all();
        delay(500);
        drive_backwards();
        delay(750);
        stop_all();
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
  Distance_back = (time_back / 2) * 0.03432;
  delay(50);

  // display only distance < 100
  if (Distance_back < 1000) 
  {
    // display measurement data
    Serial.print("Distance from back in cm: ");
    Serial.println(Distance_back);
  }
  if (Distance_back < 40) {
       Serial.print("Obstacle detected back side");
        stop_all(); // stop all
        delay(500);
        // drive backwards
        drive_forwards();
        delay(750);
        stop_all();
}

//////////////// Obstacle Detector left  ////////////////////
// this sensor gives 0 for an obstacle and 1 regularly.
  int Distance_left = digitalRead(12); // Read the sensor output

  Serial.print("Distance from left: ");
  Serial.println(Distance_left); // Print the sensor output

  if (Distance_left == 0) {
    Serial.println("Obstacle detected from left"); // Output "Hallo" if sensor value is 0
    bypass_left();
  }

  delay(500); // Wait half a second

//////////////// Obstacle Detector right  ////////////////////
// this sensor gives 0 for an obstacle and 1 regularly.
  int Distance_right = digitalRead(2); // Read the sensor output

  Serial.print("Distance from right: ");
  Serial.println(Distance_right); // Print the sensor output

  if (Distance_right == 0) {
    Serial.println("Obstacle detected from right"); // Output "Hallo" if sensor value is 0
    bypass_right();
  
  delay(500); // Wait half a second
}
}