/* 
#===============================================================================
#
#          FILE:  Arduino-mit-Fernbedienung-steuern_Hinterniserkennung.ino
#         USAGE:  Only compatible with Arduino IDE
#
#   DESCRIPTION:
#
#       OPTIONS:  ---
#  REQUIREMENTS:  Arduino, Arduino-Desktopapp, IRremote 4.3.1 by shirriff
#          BUGS:  ---
#         NOTES:  I'm using version 4 of the IRremote Libary. With a different version, parts may not work.
#        AUTHOR:  Niclas Heinz, niclas.heinz@hpost.net
#       COMPANY:  - 
<<<<<<< Projekte/Arduino-mit-Fernbedienung-steuern_Hinterniserkennung/Arduino-mit-Fernbedienung-steuern_Hinterniserkennung.ino
#       VERSION:  4.3
=======
#      REVISION:  ---
#===============================================================================
 */


#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11
int TRIGGER_front = 4; // Pin für den Sender
int TRIGGER_right = 12;
int TRIGGER_left = 7;
int ECHO_front = 3; 
int ECHO_right = 13;
int ECHO_left = 8;
// Variable for saving the distance
long Distance_front = 0; 
long Distance_right = 0; 
long Distance_left = 0;
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

// Manöver, die der Arduino unterstützt

void drive_forwards() {
       Serial.println("Drive forwards (2)");
        digitalWrite(6, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(9, LOW);
        analogWrite(10, 230);
        digitalWrite(2, HIGH);
}

void drive_backwards() {
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

void stop_all() {
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

void turn_left() {
        Serial.println("Turn left (9)");
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(2, LOW);
        digitalWrite(9, HIGH);
        digitalWrite(6, LOW);
        delay(250);
        digitalWrite(9, LOW);
}
void turn_right() {
        Serial.println("Turn right (4)");
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(2, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(10, LOW);
        delay(250);
        digitalWrite(6, LOW);
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

//////////////// Entfernungsmesser front  ////////////////////
digitalWrite(TRIGGER_front, LOW);
 // delay(5);

  // Signal für 10 Micrsekunden senden, danach wieder ausschalten
  digitalWrite(TRIGGER_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_front, LOW);

  // pulseIn -> Zeit messen, bis das Signal zurückkommt
  long time_front = pulseIn(ECHO_front, HIGH);

  // Entfernung in cm berechnen
  // Zeit/2 -> nur eine Strecke
  Distance_front = (time_front / 2) * 0.03432;
  delay(50);

  // nur Entfernungen < 100 anzeigen
  if (Distance_front < 1000) 
  {
    // Messdaten anzeigen
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
//////////////// Entfernungsmesser right  ////////////////////
digitalWrite(TRIGGER_right, LOW);
  delay(5);

  // Signal für 10 Micrsekunden senden, danach wieder ausschalten
  digitalWrite(TRIGGER_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_right, LOW);

  // pulseIn -> Zeit messen, bis das Signal zurückkommt
  long time_right = pulseIn(ECHO_right, HIGH);

  // Entfernung in cm berechnen
  // Zeit/2 -> nur eine Strecke
  Distance_right = (time_right / 2) * 0.03432;
  delay(50);

  // nur Entfernungen < 100 anzeigen
  if (Distance_right < 1000) 
  {
    // Messdaten anzeigen
    Serial.print("Entfernung r in cm: ");
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
//////////////// Entfernungsmesser left  ////////////////////
digitalWrite(TRIGGER_left, LOW);
  delay(5);

  // Signal für 10 Micrsekunden senden, danach wieder ausschalten
  digitalWrite(TRIGGER_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_left, LOW);

  // pulseIn -> Zeit messen, bis das Signal zurückkommt
  long time_left = pulseIn(ECHO_left, HIGH);

  // Entfernung in cm berechnen
  // Zeit/2 -> nur eine Strecke
  Distance_left = (time_left / 2) * 0.03432;
  delay(5);

  // nur Entfernungen < 100 anzeigen
  if (Distance_left < 1000) 
  {
    // Messdaten anzeigen
    Serial.print("Entfernung r in cm: ");
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

}
