#include <IRremote.hpp>
#define IR_RECEIVE_PIN 11
int Kommando = (IrReceiver.decodedIRData.decodedRawData, HEX); // New essential definition vor the usage of the new libary
void setup()
{
Serial.begin(9600);
pinMode(4, OUTPUT); // PIN  for LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {

if (IrReceiver.decode()) 
{
Serial.println(IrReceiver.decodedIRData.decodedRawData, DEC); // Print "old" raw data
//IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
//IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
switch (IrReceiver.decodedIRData.decodedRawData){
  case 4161273600:
  Serial.println("aha");
  digitalWrite(4, HIGH);
  break;
  case 4177985280:
  Serial.println("es funktioniert");
  digitalWrite(4, LOW);
  break;
  case 4027580160:
  Serial.println("blinken");
  digitalWrite(4, HIGH),
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);
  break;
  
}



IrReceiver.resume(); // Enable receiving of the next value

}





}