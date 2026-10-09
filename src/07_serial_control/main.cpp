#include <Arduino.h>

// Kontrol LED lewat Serial Monitor. Ketik perintah lalu tekan Enter:
//   1 50   -> LED 1 kecerahan 50%
//   2 100  -> LED 2 kecerahan 100%
//   on     -> kedua LED 100%
//   off    -> kedua LED mati
//   help   -> tampilkan bantuan

const int LED_PINS[2] = {D1, D2};

void setLed(int index, int persen) {
  persen = constrain(persen, 0, 100);
  float f = persen / 100.0f;
  analogWrite(LED_PINS[index], (int)(f * f * 1023));
  Serial.printf("LED %d = %d%%\n", index + 1, persen);
}

void bantuan() {
  Serial.println("Perintah: '1 50' (LED 1 50%), '2 100', 'on', 'off', 'help'");
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 2; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    analogWrite(LED_PINS[i], 0);
  }
  Serial.println();
  bantuan();
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');
  line.trim();
  line.toLowerCase();
  if (line.length() == 0) return;

  if (line == "on") {
    setLed(0, 100);
    setLed(1, 100);
  } else if (line == "off") {
    setLed(0, 0);
    setLed(1, 0);
  } else if (line == "help") {
    bantuan();
  } else {
    int spasi = line.indexOf(' ');
    int led = line.substring(0, spasi).toInt();
    if (spasi > 0 && (led == 1 || led == 2)) {
      setLed(led - 1, line.substring(spasi + 1).toInt());
    } else {
      Serial.println("Perintah tidak dikenal. Ketik 'help'.");
    }
  }
}
