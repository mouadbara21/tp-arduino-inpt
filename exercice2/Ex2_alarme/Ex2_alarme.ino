const int pinPIR = 2;
const int pinLED = 13;
const int pinBuzzer = 10;

bool estArme = false;
bool alarmeActive = false;
unsigned long debutSonnerie = 0;
const long dureeMaxBuzzer = 3000;

void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(9600);
  Serial.println("Systeme pret. 'A' pour Armer, 'D' pour Desarmer.");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'A') {
      estArme = true;
      Serial.println(">>> SYSTEME ARME");
    } else if (cmd == 'D') {
      estArme = false;
      alarmeActive = false;
      digitalWrite(pinLED, LOW);
      noTone(pinBuzzer);
      Serial.println(">>> SYSTEME DESARME");
    }
  }

  int detection = digitalRead(pinPIR);
  if (estArme && detection == HIGH && !alarmeActive) {
    alarmeActive = true;
    debutSonnerie = millis();
    Serial.println("!!! ALERTE : INTRUSION DETECTEE !!!");
  }

  if (alarmeActive) {
    if (millis() - debutSonnerie < dureeMaxBuzzer) {
      digitalWrite(pinLED, HIGH);
      tone(pinBuzzer, 2000);
    } else {
      digitalWrite(pinLED, LOW);
      noTone(pinBuzzer);
      if (digitalRead(pinPIR) == LOW) {
        alarmeActive = false;
      }
    }
  }
}
