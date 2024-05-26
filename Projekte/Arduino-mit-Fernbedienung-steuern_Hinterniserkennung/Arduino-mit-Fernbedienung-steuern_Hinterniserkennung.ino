/* 
#===============================================================================
#
#          FILE:  Projekt_12_IRFernbediengung_Motorsteuerung.ino
#
#         USAGE:  Only compatible with Arduino ICE
#
#   DESCRIPTION:
#
#       OPTIONS:  ---
#  REQUIREMENTS:  Arduino, Arduino-Desktopapp, IRremote V 2.2.3
#          BUGS:  ---
#         NOTES:  I'm using version 2.2.3 of the IRremote Libary. With a different version, parts may not work.
#        AUTHOR:  Niclas Heinz, nh@hpost.net
#       COMPANY:  - 
#       VERSION:  2.0
#      REVISION:  ---
#===============================================================================
 */
/*
* IRremote: IRrecvDemo - demonstrates
receiving IR codes with IRrecv
* An IR detector/demodulator must be
connected to the input RECV_PIN.
* Version 0.1 July, 2009
* Copyright 2009 Ken Shirriff
* http://arcfn.com
*/   
//Infromationen über das ursprüngliche Programm „IrrecvDemo“.


#include <IRremote.h>  


IRrecv irrecv(RECV_PIN);   // Infrarotsensor an Pin 11 ausliest.
decode_results results;  // Dieser Befehl sorgt dafür, dass die Daten, die per Infrarot eingelesen werden unter „results“ abgespeichert werden.

// Variablen
int SENDEN = 7; // Pin für den Sender
int RECV_PIN = 11; // Infrarotsensor
int mo_li_1 = 6;
int mo_li_2 = 7;
int mo_re_1 = 9;
int mo_re_2 = 10;
int ECHO = 3; // Pin für das vom Objekt reflektierte Signal

long Entfernung = 0; // Variable for saving the distance

void setup() {

Serial.begin(9600);    //Starting serial monitor
// Starting the receiver
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();
  Serial.println("Starting IRin");
  Serial.println("Waiting for Pings...");


//pinMode(1, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(mo_re_1, OUTPUT);
pinMode(mo_re_2, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(mo_li_2, OUTPUT);
pinMode(mo_li_2, OUTPUT);
pinMode(SENDEN, OUTPUT);
pinMode(ECHO, INPUT);

// Seriellen Monitor starten
Serial.begin(9600);
}

void loop()

{   //Der loop-Teil fällt durch den Rückgriff auf die „library“ sehr kurz aus. 

if (irrecv.decode(&results)) {    //Wenn Daten empfangen wurden,

Serial.println(results.value, DEC); //werden sie als Dezimalzahl (DEC) an den Serial-Monitor ausgegeben.

if (results.value == 16738455) {
  Serial.println("Light off (0)");
  digitalWrite(2, LOW);
}
if (results.value == 16724175) {
  Serial.println("Light on (1)");
  digitalWrite(2, HIGH);
}

// Drive forwards
if (results.value == 16718055) {
  Serial.println("motors on (2)");
  digitalWrite(8, HIGH);
  digitalWrite(mo_re_1, HIGH);
  analogWrite(mo_re_1, 230);
  digitalWrite(2, HIGH);
  digitalWrite(mo_li_2, LOW);
  digitalWrite(mo_re_2, LOW);
}

// Drive backwards
if (results.value == 16743045) {
  Serial.println("Drive backwards (3)");
  digitalWrite(8, LOW);
  digitalWrite(mo_re_1, LOW);
  digitalWrite(2, LOW);

    analogWrite(mo_li_2, 70);
  analogWrite(mo_re_2, 70);

  delay(500);
  analogWrite(mo_li_2, 150);
  analogWrite(mo_re_2, 150);

  delay(500);
  digitalWrite(mo_li_2, HIGH);
  digitalWrite(mo_re_2, HIGH); 
  
}

// Turn right 
if (results.value == 16716015) {
  Serial.println("Drehung nach rechts (4)");
  digitalWrite(8, LOW);
  digitalWrite(mo_re_1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(mo_li_2, HIGH);
  digitalWrite(mo_re_2, LOW);
  delay(250);
  digitalWrite(mo_li_2, LOW);
}

// Turn left
if (results.value == 16726215) {
  Serial.println("Drehung nach links (mo_re_1)");
  digitalWrite(8, LOW);
  digitalWrite(mo_re_1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(mo_li_2, LOW);
  delay(250);
  digitalWrite(8, LOW);
}

if (results.value == 16743045) {
  Serial.println("Alles aus (Ein/Aus)");
  digitalWrite(8, LOW);
  digitalWrite(mo_re_1, LOW);
  digitalWrite(2, LOW);
}


// cancel all commands and turn off
if (results.value == 16753245) {
  Serial.println("Motor aus (3)");
  digitalWrite(mo_li_2, LOW);
  digitalWrite(mo_li_2, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(mo_re_2, LOW);
  digitalWrite(mo_re_1, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);

}

irrecv.resume();  //Der nächste Wert soll vom IR-Empfänger eingelesen werden

}


  ////////////////. NEEDS TO BE VERIFIED!!!  ////////////////////
// Sender kurz ausschalten um Störungen des Signal zu vermeiden
  digitalWrite(SENDEN, LOW);
  delay(mo_re_1);

  // Signal für mo_li_2 Microsekunden senden, danach wieder ausschalten
  digitalWrite(SENDEN, HIGH);
  delayMicroseconds(mo_li_2);
  digitalWrite(SENDEN, LOW);

  // pulseIn -> Zeit messen, bis das Signal zurückkommt
  long Zeit = pulseIn(ECHO, HIGH);

  // Entfernung in cm berechnen
  // Zeit/2 -> nur eine Strecke
  Entfernung = (Zeit / 2) * 0.03432;
  delay(500);

  // nur Entfernungen < 100 anzeigen
  if (Entfernung < 1000) 
  {
    // Messdaten anzeigen
   Serial.print("Entfernung in cm: ");
   Serial.println(Entfernung);
  }

   if (Entfernung < 40) {
        Serial.print("Entfernung kleiner als 20 cm ");
  digitalWrite(mo_li_2, LOW);
  digitalWrite(mo_li_2, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(mo_re_2, LOW);
  digitalWrite(mo_re_1, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(2, LOW);

  digitalWrite(8, LOW);
  digitalWrite(mo_re_1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(mo_li_2, HIGH);
  digitalWrite(mo_re_2, LOW);
  delay(600);
  digitalWrite(mo_li_2, LOW);  
  }
}

