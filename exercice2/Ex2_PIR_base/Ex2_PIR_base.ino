int pinEntree = 2;
int etatPir = LOW;
int val = 0;

void setup() {
  pinMode(pinEntree, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(pinEntree);
  if (val == HIGH) {
    if (etatPir == LOW) {
      Serial.println("Mouvement detecte!");
      Serial.println(val);
      etatPir = HIGH;
    }
  } else {
    if (etatPir == HIGH) {
      Serial.println("Mouvement termine!");
      Serial.println(val);
      etatPir = LOW;
    }
  }
}
