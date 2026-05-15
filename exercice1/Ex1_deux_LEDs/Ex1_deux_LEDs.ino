const int LED1_PIN = 9;
const int LED2_PIN = 10;
long P1 = 1000;
long P2 = 1000;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= P1) {
    previousMillis1 = currentMillis;
    digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
  }
  if (currentMillis - previousMillis2 >= P2) {
    previousMillis2 = currentMillis;
    digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
  }
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toUpperCase();
    if (input.startsWith("P1")) {
      long v = input.substring(2).toInt();
      if (v > 0) { P1 = v; Serial.print("P1 mis a jour : "); Serial.println(P1); }
    } else if (input.startsWith("P2")) {
      long v = input.substring(2).toInt();
      if (v > 0) { P2 = v; Serial.print("P2 mis a jour : "); Serial.println(P2); }
    }
  }
}
