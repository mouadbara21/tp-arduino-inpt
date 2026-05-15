#include <AFMotor.h>

AF_DCMotor motor(4);

enum ModeVentilateur { OFF, ECO, NORMAL, TURBO };
ModeVentilateur etatActuel = OFF;
int vitesseActuelle = 0;
int vitesseCible = 0;

void setup() {
  Serial.begin(9600);
  motor.setSpeed(0);
  motor.run(FORWARD);
  Serial.println("--- Systeme Robuste ---");
  Serial.println("Commandes valides : 0, 1, 2, 3");
}

void gererRampe() {
  if (vitesseActuelle < vitesseCible) {
    vitesseActuelle++;
    motor.setSpeed(vitesseActuelle);
    delay(10);
  } else if (vitesseActuelle > vitesseCible) {
    vitesseActuelle--;
    motor.setSpeed(vitesseActuelle);
    delay(10);
  }
  if (vitesseActuelle == 0) motor.run(RELEASE);
  else motor.run(FORWARD);
}

void loop() {
  if (Serial.available() > 0) {
    char car = Serial.peek();
    if (car >= '0' && car <= '3') {
      char commande = Serial.read();
      switch (commande) {
        case '0': vitesseCible = 0;   Serial.println("Cible: OFF");    break;
        case '1': vitesseCible = 100; Serial.println("Cible: ECO");    break;
        case '2': vitesseCible = 180; Serial.println("Cible: NORMAL"); break;
        case '3': vitesseCible = 255; Serial.println("Cible: TURBO");  break;
      }
    } else if (car == '\n' || car == '\r') {
      Serial.read();
    } else {
      Serial.read();
      Serial.print("ERREUR SECURITE : Entree '");
      Serial.print(car);
      Serial.println("' rejetee.");
      while (Serial.available() > 0) Serial.read();
    }
  }
  gererRampe();
}
