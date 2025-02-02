/* 
#===============================================================================
#
#          FILE:  sensor_range-finder.ino
#
#         USAGE:  Only compatible with Arduino ICE
#
#   DESCRIPTION:
#
#       OPTIONS:  ---
#  REQUIREMENTS:  Arduino, Arduino-Desktopapp, 
#          BUGS:  ---
#         NOTES:  I'm using version 4 of the IRremote Libary. With a different version, parts may not work.
#        AUTHOR:  Niclas Heinz, nh@hpost.net
#       COMPANY:  - 
#       VERSION:  2.0
#      REVISION:  ---
#===============================================================================
 */


#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11
int Kommando = (IrReceiver.decodedIRData.decodedRawData, HEX);  // New essential definition vor the usage of the new libary

int SENDEN = 2; // Pin für den Sender
int ECHO = 13; // Pin für das vom Objekt reflektierte Signal
long Entfernung = 0; // Variable für die Speicherung der Entfernung
void setup() {

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
  Serial.begin(9600);        //Serielle kommunikation starten, damit man sich später die Werte am serial monitor ansehen kann.
  pinMode(4, OUTPUT);  // 4-Pin ist ein Ausgang
  pinMode(SENDEN, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
// Sender kurz ausschalten um Störungen des Signal zu vermeiden
// Sender kurz ausschalten um Störungen des Signal zu vermeiden
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
        Serial.println("Alles aus (Ein/Aus)");
        Serial.println("Motor aus (3)");
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(8, LOW);
        digitalWrite(7, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
        digitalWrite(4, LOW);
        digitalWrite(3, LOW);
        digitalWrite(2, LOW);
        delay(1000);
        // drive backwards
        Serial.println("motors on (2)");
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        analogWrite(9, 230);
        digitalWrite(2, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(10, LOW);
        delay(2000);
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
}
