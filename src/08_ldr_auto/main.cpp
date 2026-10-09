#include <Arduino.h>

// Lampu otomatis: makin gelap, LED 1 makin terang. LED 2 menyala saat sangat gelap.
//
// Wiring modul LDR: VCC -> 3V3, GND -> G, AO -> A0 (satu-satunya pin analog).
// Pin A0 NodeMCU hanya boleh menerima 0-3.3V, jadi jangan sambungkan ke 5V.
//
// Buka Serial Monitor untuk melihat nilai sensor. Kalau LED malah menyala saat
// terang, ubah GELAP_NILAI_TINGGI (modul LDR berbeda-beda arahnya).

const int LED1_PIN = D1;
const int LED2_PIN = D2;
const bool GELAP_NILAI_TINGGI = false;
const int AMBANG_GELAP = 700;  // 0 (terang) sampai 1023 (gelap)

int gamma(int v) {
  return (long)v * v / 1023;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  int nilai = analogRead(A0);
  int gelap = GELAP_NILAI_TINGGI ? nilai : 1023 - nilai;  // 0 = terang, 1023 = gelap

  analogWrite(LED1_PIN, gamma(gelap));
  digitalWrite(LED2_PIN, gelap > AMBANG_GELAP ? HIGH : LOW);

  Serial.printf("sensor=%d gelap=%d\n", nilai, gelap);
  delay(150);
}
