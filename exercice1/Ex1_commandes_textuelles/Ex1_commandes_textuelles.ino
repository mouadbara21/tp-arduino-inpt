const int LED_PIN = 9;
String command = "";
bool isBlinking = false;
unsigned long previousMillis = 0;
const long interval = 500;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();
    if (command == "allumer")        { isBlinking = false; digitalWrite(LED_PIN, HIGH); Serial.println("LED allumee"); }
    else if (command == "eteindre")  { isBlinking = false; digitalWrite(LED_PIN, LOW);  Serial.println("LED eteinte"); }
    else if (command == "inverser")  { isBlinking = false; digitalWrite(LED_PIN, !digitalRead(LED_PIN)); Serial.println("Etat inverse"); }
    else if (command == "clignoter") { isBlinking = true;  Serial.println("Mode clignotement actif"); }
  }
  if (isBlinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
  }
}
