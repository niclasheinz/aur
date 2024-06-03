  int zaehler = 0; // 
 void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // initialisieren des seriellen Monitors und dessen Port
  Serial.println("Hallo Welt. Das wird nur einmal ausgegeben.");
  pinMode(6, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Zaehlerstand: ");
  Serial.println(zaehler);
  delay(1000);
  zaehler = zaehler + 1;

  if (zaehler == 20) {
    Serial.println("Zaehlerstand ist jetzt 20");
    digitalWrite(6, HIGH); // legt Spannung auf Pin 6
    
  }

  if (zaehler == 41) {
    digitalWrite(3, HIGH); // legt Spannung auf Pin 5
    exit(0);
  }
 
}
