#include <Arduino.h>

// Saat LED 1 makin terang, LED 2 makin redup, lalu sebaliknya (seperti ayunan).

const int LED1_PIN = D1;
const int LED2_PIN = D2;
const int LANGKAH = 8;
const int JEDA_MS = 8;

int gamma(int v) {
  return (long)v * v / 1023;
}

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  for (int v = 0; v <= 1023; v += LANGKAH) {
    analogWrite(LED1_PIN, gamma(v));
    analogWrite(LED2_PIN, gamma(1023 - v));
    delay(JEDA_MS);
  }
  for (int v = 1023; v >= 0; v -= LANGKAH) {
    analogWrite(LED1_PIN, gamma(v));
    analogWrite(LED2_PIN, gamma(1023 - v));
    delay(JEDA_MS);
  }
}
