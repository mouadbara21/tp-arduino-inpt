#include <AFMotor.h>
#include <Servo.h>

AF_Stepper stepper(2048, 2);
Servo servoPorte;

const int pinPIR = A0;
int etatPir = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(pinPIR, INPUT);
  servoPorte.attach(9);
  servoPorte.write(0);
  stepper.setSpeed(10);
  Serial.println("Systeme Pret : Servo sur SER2, PIR sur A0");
}

void loop() {
  int lecture = digitalRead(pinPIR);
  if (lecture == HIGH && etatPir == LOW) {
    Serial.println(">>> MOUVEMENT ! Ouverture en cours...");
    servoPorte.write(90);
    stepper.step(500, FORWARD, MICROSTEP);
    etatPir = HIGH;
    Serial.println("Porte Ouverte. En attente de fin de mouvement...");
  } else if (lecture == LOW && etatPir == HIGH) {
    Serial.println(">>> Calme detecte. Fermeture dans 3s...");
    delay(3000);
    servoPorte.write(0);
    stepper.step(500, BACKWARD, MICROSTEP);
    etatPir = LOW;
    Serial.println("Porte Fermee. Systeme pret pour nouvelle detection.");
  }
}
