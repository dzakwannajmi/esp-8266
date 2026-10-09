#include <Arduino.h>

// LED 1 dan LED 2 hidup dan mati bersamaan.
// Ubah JEDA untuk mengatur kecepatan kedip (dalam milidetik).

const int LED1_PIN = D1;
const int LED2_PIN = D2;
const int JEDA = 300;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  delay(JEDA);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  delay(JEDA);
}
