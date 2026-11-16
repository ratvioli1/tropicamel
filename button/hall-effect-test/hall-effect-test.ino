const int hallPin = D10;

void setup() {
  Serial.begin(115200);
  pinMode(hallPin, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(hallPin) == LOW ? "Detected" : "Not detected");
  delay(250);
}