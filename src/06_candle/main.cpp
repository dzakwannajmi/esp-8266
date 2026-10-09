#include <Arduino.h>

// Efek api lilin: kecerahan acak dan berubah-ubah, tiap LED sendiri-sendiri.

const int LED1_PIN = D1;
const int LED2_PIN = D2;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  randomSeed(micros());
}

void loop() {
  analogWrite(LED1_PIN, random(250, 1024));
  analogWrite(LED2_PIN, random(250, 1024));
  delay(random(40, 140));
}
