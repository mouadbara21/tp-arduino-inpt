int led = 9;
char octet_rx = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    octet_rx = Serial.read();
    delay(5000);
    if (octet_rx == 'a') { digitalWrite(led, HIGH); Serial.println("LED allumee"); }
    if (octet_rx == 'e') { digitalWrite(led, LOW);  Serial.println("LED eteinte"); }
  }
}
