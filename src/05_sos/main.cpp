#include <Arduino.h>

// Sinyal SOS morse: ... --- ...  (titik pendek, garis panjang), diulang terus.
// Kedua LED menyala bersamaan.

const int LED1_PIN = D1;
const int LED2_PIN = D2;
const int TITIK = 200;         // durasi titik (ms)
const int GARIS = TITIK * 3;   // durasi garis
const int ANTAR_SINYAL = TITIK;

void kedip(int durasi) {
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  delay(durasi);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  delay(ANTAR_SINYAL);
}

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < 3; i++) kedip(TITIK);  // S
  delay(TITIK * 2);
  for (int i = 0; i < 3; i++) kedip(GARIS);  // O
  delay(TITIK * 2);
  for (int i = 0; i < 3; i++) kedip(TITIK);  // S
  delay(TITIK * 10);                          // jeda sebelum mengulang
}
