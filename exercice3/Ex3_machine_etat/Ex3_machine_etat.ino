#include <AFMotor.h>

AF_DCMotor motor(4);

enum ModeVentilateur { OFF, ECO, NORMAL, TURBO };
ModeVentilateur etatActuel = OFF;

void setup() {
  Serial.begin(9600);
  motor.setSpeed(0);
  motor.run(RELEASE);
  Serial.println("=== Interface de Controle ===");
  Serial.println("Tapez 0 pour OFF");
  Serial.println("Tapez 1 pour ECO");
  Serial.println("Tapez 2 pour NORMAL");
  Serial.println("Tapez 3 pour TURBO");
}

void executerMode() {
  switch (etatActuel) {
    case OFF:    Serial.println("Mode : OFF -> Moteur arrete.");    motor.setSpeed(0);   motor.run(RELEASE); break;
    case ECO:    Serial.println("Mode : ECO -> Vitesse 100.");      motor.setSpeed(100); motor.run(FORWARD); break;
    case NORMAL: Serial.println("Mode : NORMAL -> Vitesse 180.");   motor.setSpeed(180); motor.run(FORWARD); break;
    case TURBO:  Serial.println("Mode : TURBO -> Vitesse 255.");    motor.setSpeed(255); motor.run(FORWARD); break;
  }
}

void loop() {
  if (Serial.available() > 0) {
    char commande = Serial.read();
    switch (commande) {
      case '0': etatActuel = OFF;    break;
      case '1': etatActuel = ECO;    break;
      case '2': etatActuel = NORMAL; break;
      case '3': etatActuel = TURBO;  break;
      case '\n': case '\r': return;
      default: Serial.println("Erreur: Commande non reconnue. Entrez 0, 1, 2 ou 3."); return;
    }
    executerMode();
  }
}
