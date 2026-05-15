const int pinPIR = 2;
const int pinLED = 13;

void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Observation de la duree d allumage...");
}

void loop() {
  int etat = digitalRead(pinPIR);
  if (etat == HIGH) {
    digitalWrite(pinLED, HIGH);
    Serial.println("SIGNAL HAUT : LED Allumee");
  } else {
    digitalWrite(pinLED, LOW);
    Serial.println("SIGNAL BAS : LED Eteinte");
  }
  delay(100);
}
