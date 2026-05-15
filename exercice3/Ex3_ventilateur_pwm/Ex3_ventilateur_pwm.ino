#include <AFMotor.h>

AF_DCMotor motor(4);

void setup() {
  Serial.begin(9600);
  Serial.println("=== Controle du Ventilateur ===");
  Serial.println("Entrez une valeur entre 0 (Arret) et 255 (Max) :");
  motor.setSpeed(0);
  motor.run(RELEASE);
}

void loop() {
  if (Serial.available() > 0) {
    int vitesseInput = Serial.parseInt();
    if (vitesseInput >= 0 && vitesseInput <= 255) {
      Serial.print("Vitesse reglee sur : ");
      Serial.println(vitesseInput);
      motor.setSpeed(vitesseInput);
      if (vitesseInput == 0) motor.run(RELEASE);
      else motor.run(FORWARD);
    } else {
      Serial.println("Erreur : Veuillez entrer une valeur entre 0 et 255.");
    }
    while (Serial.available() > 0) Serial.read();
  }
}
