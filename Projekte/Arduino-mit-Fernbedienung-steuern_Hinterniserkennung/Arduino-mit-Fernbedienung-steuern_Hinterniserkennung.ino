/* 
#===============================================================================
#
#          FILE:  Arduino-mit-Fernbedienung-steuern_Hinterniserkennung.ino
#
#         USAGE:  Only compatible with Arduino ICE
#
#   DESCRIPTION:
#
#       OPTIONS:  ---
#  REQUIREMENTS:  Arduino, Arduino-Desktopapp, IRremote 4
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
int Kommando = (IrReceiver.decodedIRData.decodedRawData, HEX); // New essential definition vor the usage of the new libary
void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT); // PIN  for LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}


// Variablen

int mo_li_1 = 6;
int mo_li_2 = 7;
int mo_re_1 = 9;
int mo_re_2 = 10;

// Für Entfernungsmesser
int trigger=7; //Trigger-Pin des Ultraschallsensors an Pin7 des Arduino-Boards 
int echo=4; // Echo-Pim des Ultraschallsensors an Pin6 des Arduino-Boards 
long dauer=0; // Das Wort dauer ist jetzt eine Variable, unter der die Zeit gespeichert wird, die eine Schallwelle bis zur Reflektion und zurück benötigt. Startwert ist hier 0.
long entfernung=0; // Das Wort „entfernung“ ist jetzt die variable, unter der die berechnete Entfernung gespeichert wird. Info: Anstelle von „int“ steht hier vor den beiden Variablen „long“. Das hat den Vorteil, dass eine größere Zahl gespeichert werden kann. Nachteil: Die Variable benötigt mehr Platz im Speicher.

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
Serial.begin (9600); //Serielle kommunikation starten, damit man sich später die Werte am serial monitor ansehen kann.
pinMode(trigger, OUTPUT); // Trigger-Pin ist ein Ausgang
pinMode(echo, INPUT); // Echo-Pin ist ein Eingang

// Seriellen Monitor starten
Serial.begin(9600);
}

void loop() {   //Der loop-Teil fällt durch den Rückgriff auf die „library“ sehr kurz aus. 

if (IrReceiver.decode()) {

  Serial.println(IrReceiver.decodedIRData.decodedRawData, DEC); // Print "old" raw data
  //IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
  //IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
  switch (IrReceiver.decodedIRData.decodedRawData){
      case $zahl_1: //Drive forwards
        Serial.println("motors on (2)");
        digitalWrite(8, HIGH);
        digitalWrite(mo_re_1, HIGH);
        analogWrite(mo_re_1, 230);
        digitalWrite(2, HIGH);
        digitalWrite(mo_li_2, LOW);
        digitalWrite(mo_re_2, LOW);
      break;
      case $zahl_2: // drive backwards
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
      break;
      case $zahl_3: // turn right
        Serial.println("Drehung nach rechts (4)");
        digitalWrite(8, LOW);
        digitalWrite(mo_re_1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(mo_li_2, HIGH);
        digitalWrite(mo_re_2, LOW);
        delay(250);
        digitalWrite(mo_li_2, LOW);
      break;
      case $zahl_4: // turn left
        Serial.println("Drehung nach links (mo_re_1)");
        digitalWrite(8, LOW);
        digitalWrite(mo_re_1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(mo_li_2, LOW);
        delay(250);
        digitalWrite(8, LOW);
      break;
      case $on_off: // force stop all motors
        Serial.println("Alles aus (Ein/Aus)");
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
  }

IrReceiver.resume(); // Enable receiving of the next value

}

  //////////////// Entfernungsmesser  ////////////////////
// Sender kurz ausschalten um Störungen des Signal zu vermeiden
digitalWrite(trigger, LOW); 
delay(5); 
digitalWrite(trigger, HIGH); 
delay(10); 
digitalWrite(trigger, LOW);
dauer = pulseIn(echo, HIGH);
entfernung = (dauer/2) * 0.03432; 
if (entfernung >= 500 || entfernung <= 0) { 
Serial.println("Kein Messwert");
}
else { //  Ansonsten…
Serial.print(entfernung); 
Serial.println(" cm"); 
}
delay(750); 
}

  // nur Entfernungen < 100 anzeigen
  if (entfernung < 100) {
    // Messdaten anzeigen
   Serial.print("Entfernung in cm: ");
   Serial.println(entfernung);
  }

   if (entfernung < 40) {
  Serial.print("Entfernung kleiner als 40 cm ");
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

