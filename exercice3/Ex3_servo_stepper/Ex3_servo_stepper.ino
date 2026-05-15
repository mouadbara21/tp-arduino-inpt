#include <AFMotor.h>
#include <Servo.h>

AF_Stepper stepper(2048, 2);
Servo monServo;

void setup() {
  Serial.begin(9600);
  monServo.attach(9);
  stepper.setSpeed(10);
  Serial.println("--- Interface Question 6 (SERVO_2) ---");
  Serial.println("Commandes Servo : 'S' suivi de l'angle (ex: S90)");
  Serial.println("Commandes Stepper : 'F' (Avant), 'B' (Arriere)");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'S') {
      int angle = Serial.parseInt();
      if (angle >= 0 && angle <= 180) {
        monServo.write(angle);
        Serial.print("Servo (SER2) -> ");
        Serial.println(angle);
      }
    } else if (cmd == 'F') {
      Serial.println("Stepper -> Marche AVANT");
      stepper.step(100, FORWARD, MICROSTEP);
    } else if (cmd == 'B') {
      Serial.println("Stepper -> Marche ARRIERE");
      stepper.step(100, BACKWARD, MICROSTEP);
    }
  }
}
