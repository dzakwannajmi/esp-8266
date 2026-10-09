#include <Arduino.h>

// Kedua LED terang-redup pelan seperti "bernapas" (fade in / fade out).
// analogWrite di ESP8266 bernilai 0-1023. Nilai dikuadratkan (gamma)
// supaya perubahan terasa merata di mata.

const int LED1_PIN = D1;
const int LED2_PIN = D2;
const int LANGKAH = 8;     // makin besar, makin cepat berubah
const int JEDA_MS = 8;     // jeda tiap langkah

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
    analogWrite(LED2_PIN, gamma(v));
    delay(JEDA_MS);
  }
  for (int v = 1023; v >= 0; v -= LANGKAH) {
    analogWrite(LED1_PIN, gamma(v));
    analogWrite(LED2_PIN, gamma(v));
    delay(JEDA_MS);
  }
}
