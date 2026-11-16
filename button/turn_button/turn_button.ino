/*
The Arcade connectors I got can cleanly connect to ports, so it's easier  
to make a port act as ground in software than add two more wires.
*/

const int ground = D0;  // COM
const int switchInput = D1; // NO

void setup() {
  Serial.begin(115200);

  digitalWrite(ground, LOW);
  pinMode(ground, OUTPUT);
  pinMode(switchInput, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(switchInput) == LOW) {
    Serial.println("Pressed");
    delay(250);
    while (digitalRead(switchInput) == LOW) {
      delay(10);
    }
  }
  delay(10);
}
