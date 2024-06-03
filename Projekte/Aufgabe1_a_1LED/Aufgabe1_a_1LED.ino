void setup() { 

  // put your setup code here, to run once: 

  pinMode(4, OUTPUT); 
  pinMode(3, OUTPUT);

  // legt Pin 4 als Ausgang fest 

} 

 

void loop() { 

  // put your main code here, to run repeatedly: 

digitalWrite(4, HIGH); // legt Spannung auf Pin 4 
digitalWrite(3, LOW); // setzt Pin 3 auf 0 Volt 


delay(1000); // wartet 1000 Millisekunden 

digitalWrite(4, LOW); // setzt Pin 4 auf 0 Volt 
digitalWrite(3, HIGH); // legt Spannung auf Pin 3


delay(1000); // wartet 1000 Millisekunden 

// Ablauf beginnt von vorne 

} 
