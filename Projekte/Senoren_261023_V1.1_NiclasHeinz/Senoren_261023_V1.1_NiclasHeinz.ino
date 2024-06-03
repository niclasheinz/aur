int licht;
int Lichtstaerke;
int zaehler = 0;

  void setup() {
 
  pinMode(6, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
 
  // put your setup code here, to run once:
 
}
 
void loop() {//;
  licht = analogRead(A0);
  Serial.print("Helligkeit   ");
  Serial.println(licht);
  delay(1000);
  zaehler = zaehler + 1;

  if (licht > 30) {
    digitalWrite(6, LOW);
  }
  
  if (licht < 30) {
    digitalWrite(6, HIGH);
  }


  if (zaehler == 1000) {
    exit(0);
  }
  }
