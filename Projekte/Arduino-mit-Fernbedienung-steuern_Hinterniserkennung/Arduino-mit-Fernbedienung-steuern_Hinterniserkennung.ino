/* 
#===============================================================================
#
#          FILE:  Arduino-with-remote-control_obstacle-detection.ino
#         USAGE:  Only compatible with Arduino Uno
# ARDUINO MODEL:  Arduino Uno
#  REQUIREMENTS:  IRremote 4.4.0 by shirriff
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
#       VERSION:  7.0.1
# LATEST COMMIT: 04.07.2024
#===============================================================================
*/

#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11

// Pins for the obstacle detectors
int TRIGGER_front = 4;
int TRIGGER_back = 7;

// Echo Pins for the obstacle detectors
int ECHO_front = 3; 
int ECHO_back = 8;


// Variable for saving the distance
long Distance_front = 0; 
long Distance_back = 0;

// Variables for the motors
int mo_re_1 = 9;
int mo_re_2 = 10;
int mo_li_1 = 5;
int mo_li_2 = 6;
int obstacle_detector_left_PIN = 12;
void setup() {
// Activate pins 
pinMode(2, INPUT); // distance sensor right
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(mo_re_1, OUTPUT);
pinMode(mo_re_2, OUTPUT);
pinMode(mo_li_2, OUTPUT);
pinMode(8, OUTPUT);
pinMode(mo_li_1, OUTPUT);
pinMode(obstacle_detector_left_PIN, INPUT); // distance sensor left
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
        Serial.println("drive_forwards()");
        Serial.println("Drive forwards (2)");
        analogWrite(mo_li_1, 150);
        analogWrite(mo_re_2, 160);
        // digitalWrite(mo_re_2, LOW);
        // digitalWrite(mo_re_1, LOW);
        delay(2000);
        stop_all();
}

void drive_forwards_bypass() {
    Serial.println("drive_forwards_bypass()");
    analogWrite(mo_re_2, 130);
    analogWrite(mo_li_1, 130);
    delay(500);
    stop_all();
}

void drive_backwards() { // driving backwards
        Serial.println("drive_backwards()");
        analogWrite(mo_re_1, 150);
        analogWrite(mo_li_2, 160);
        delay(2000);
        //stop_all();
}

void stop_all() { //stop all motors
        Serial.println("stop_all()");
        Serial.println("stop all (On/Off)");
        digitalWrite(5, LOW);
        digitalWrite(mo_li_1, LOW);
        digitalWrite(8, LOW);
        digitalWrite(mo_li_2, LOW);
        digitalWrite(mo_re_2, LOW);
        digitalWrite(mo_re_1, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
}

void turn_left() { // turning left
        Serial.println("turn_left()");
        Serial.println("Turn left (9)");
        digitalWrite(8, LOW);
        digitalWrite(mo_re_1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(mo_re_1, HIGH);
        digitalWrite(mo_li_1, LOW);
        delay(250);
        digitalWrite(mo_re_1, LOW);
}

void turn_right() { //turing right
        Serial.println("turn_right()");
        Serial.println("Drehung nach rechts (4)");
        digitalWrite(8, LOW);
        digitalWrite(mo_re_1, LOW);
        digitalWrite(3, LOW);
        digitalWrite(mo_re_2, LOW);
        delay(250);
        digitalWrite(mo_li_2, LOW);
        stop_all();
}

void turn_back() { //turning back
        Serial.println("turn_back()");
        Serial.println("Turn back (4)");;
        digitalWrite(8, LOW);
        digitalWrite(mo_re_1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(mo_li_1, HIGH);
        digitalWrite(mo_re_2, LOW);
        delay(250);
        digitalWrite(mo_li_1, LOW);
}

void bypass_left() { // function for bypass objects from left side
    Serial.println("bypass_left()");
    Serial.println("Bypass left");
    //reducing speed

    // 1. reduce speed
    // drive_forwardsbypass();
    // delay(1000);
    // drive_forwardsbypassstop();
    // turn_right();
    // delay(500);
    // stop_all();
}

void stop_back() {

}
void drive_forwardsbypass() {
          Serial.println("drive_forwardsbypass()");

    analogWrite(mo_re_2, 230);
    analogWrite(mo_li_1, 130);
    delay(500);
    drive_forwardsbypassstop();
}
void drive_forwardsbypassstop() {
          Serial.println("drive_forwardsbypasstop()");

    stop_all();
}

void bypass_right() { // function for bypass objects from right side
    Serial.println("bypass_right()");
    Serial.println("Bypass right");
    drive_forwardsbypass();
    delay(1000);
    drive_forwardsbypassstop();
    turn_left();
    delay(500);
    stop_all();
}

void force_stop(){ // if distance to one of the sensors is lower than 30 -> force stop
  if (Distance_front < 30 || Distance_back < 30) {
    Serial.println("Executing force-stop in 1s");
    stop_all();
  }
}

void drive_forwards1() {
  Serial.println("Hall");
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
   // Serial.print("Distance Front in cm: ");
   // Serial.println(Distance_front);
  }
  if (Distance_front < 40) {
        Serial.print("Obstacle detected front side");
        stop_all();
        delay(500);
        drive_backwards();
        delay(250);
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
   // Serial.print("Distance from back in cm: ");
   // Serial.println(Distance_back);
  }
  if (Distance_back < 20) {
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

  //Serial.print("Distance from left: ");
  //Serial.println(Distance_left); // Print the sensor output

  if (Distance_left == 0) {
    Serial.println("Obstacle detected from left"); // Output if sensor value is 0
    bypass_left();
  }

  delay(500); // Wait half a second

//////////////// Obstacle Detector right  ////////////////////
// this sensor gives 0 for an obstacle and 1 regularly.
  int Distance_right = digitalRead(2); // Read the sensor output

 // Serial.print("Distance from right: ");Drehung nach rechts (4)

 // Serial.println(Distance_right); // Print the sensor output

  if (Distance_right == 0) {
    Serial.println("Obstacle detected from right"); // Output "Hallo" if sensor value is 0
    bypass_right();
  
  delay(500); // Wait half a second
}
}