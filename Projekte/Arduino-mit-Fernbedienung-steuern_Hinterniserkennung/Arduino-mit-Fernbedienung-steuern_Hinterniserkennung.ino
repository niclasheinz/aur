/* 
#===============================================================================
#
#          FILE:  Arduino-mit-Fernbedienung-steuern_Hinterniserkennung.ino
#         USAGE:  Only compatible with Arduino ICE
#
#   DESCRIPTION:
#
#       OPTIONS:  ---
#  REQUIREMENTS:  Arduino, Arduino-Desktopapp, IRremote 4.3.1 by shirriff
#          BUGS:  ---
#         NOTES:  I'm using version 4 of the IRremote Libary. With a different version, parts may not work.
#        AUTHOR:  Niclas Heinz, niclas.heinz@hpost.net
#       COMPANY:  - 
#       VERSION:  2.1
#      REVISION:  ---
#===============================================================================
 */


#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11
int Kommando = (IrReceiver.decodedIRData.decodedRawData, HEX);  // New essential definition vor the usage of the new libary

int SENDEN = 4; // Pin für den Sender
int ECHO = 3; // Pin für das vom Objekt reflektierte Signal
int TRIGGER_right = 12;
int ECHO_right = 13;
long Entfernung = 0; // Variable für die Speicherung der Entfernung
long Distance_right = 0;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Start the receiver
  Serial.begin(9600);  //Starting serial monitor

  //pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(4, OUTPUT);  // 4-Pin ist ein Ausgang
  pinMode(SENDEN, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER_right,  OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);        //Serielle kommunikation starten, damit man sich später die Werte am serial monitor ansehen kann.

}

void loop() {

  if (IrReceiver.decode()) {

    Serial.println(IrReceiver.decodedIRData.decodedRawData, DEC);  // Print "old" raw data
    //IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    //IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case 4077715200:  //Drive forwards
        Serial.println("Drive forwards (2)");
        digitalWrite(6, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(9, LOW);
        analogWrite(10, 230);
        digitalWrite(2, HIGH);
        break;
      case 3877175040:  // drive backwards
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
        break;
      case 2707357440:  // turn right
        Serial.println("Turn right (4)");
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(2, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(10, LOW);
        delay(250);
        digitalWrite(6, LOW);
        break;
      case 4144561920:  // turn left
        Serial.println("Turn left (9)");
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
        digitalWrite(2, LOW);
        digitalWrite(9, HIGH);
        digitalWrite(6, LOW);
        delay(250);
        digitalWrite(9, LOW);
        break;
      
      case 3125149440:  // force stop all motors
        Serial.println("stop all (Ein/Aus)");
        Serial.println("Motors stopped (3)");
        digitalWrite(6, LOW);
        digitalWrite(6, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        digitalWrite(5, LOW);
    }
  }

  IrReceiver.resume();  // Enable receiving of the next value

//////////////// Entfernungsmesser front  ////////////////////
digitalWrite(SENDEN, LOW);
 // delay(5);

  // Signal für 10 Micrsekunden senden, danach wieder ausschalten
  digitalWrite(SENDEN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENDEN, LOW);

  // pulseIn -> Zeit messen, bis das Signal zurückkommt
  long Zeit = pulseIn(ECHO, HIGH);

  // Entfernung in cm berechnen
  // Zeit/2 -> nur eine Strecke
  Entfernung = (Zeit / 2) * 0.03432;
  delay(50);

  // nur Entfernungen < 100 anzeigen
  if (Entfernung < 1000) 
  {
    // Messdaten anzeigen
    Serial.print("Entfernung in cm: ");
    Serial.println(Entfernung);
  }
  if (Entfernung < 40) {
    Serial.print("unter 40");
    
}

//////////////// Entfernungsmesser front  ////////////////////
digitalWrite(TRIGGER_right, LOW);
 // delay(5);

  // Signal für 10 Micrsekunden senden, danach wieder ausschalten
  digitalWrite(TRIGGER_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_right, LOW);

  // pulseIn -> Zeit messen, bis das Signal zurückkommt
  long Zeit = pulseIn(ECHO_right, HIGH);

  // Entfernung in cm berechnen
  // Zeit/2 -> nur eine Strecke
  Distance_right = (Zeit / 2) * 0.03432;
  delay(50);

  // nur Entfernungen < 100 anzeigen
  if (Distance_right < 1000) 
  {
    // Messdaten anzeigen
    Serial.print("Entfernung r in cm: ");
    Serial.println(Distance_right);
  }
  if (TRIGGER_right < 40) {
    Serial.print("unter 40");
    
}
}