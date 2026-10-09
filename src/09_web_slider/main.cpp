#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "secrets.h"

// Kontrol kecerahan 2 LED lewat halaman web (slider).
// Wiring: D1 -> 220 ohm -> LED1 -> GND, D2 -> 220 ohm -> LED2 -> GND.

const int LED_PINS[2] = {D1, D2};  // GPIO 5 dan GPIO 4
int level[2] = {0, 0};             // persen, 0-100

ESP8266WebServer server(80);

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Kontrol LED</title>
<style>
  body{font-family:system-ui,sans-serif;max-width:420px;margin:2rem auto;padding:0 1rem}
  h1{font-size:1.3rem}
  .card{border:1px solid #ccc;border-radius:12px;padding:1rem;margin-bottom:1rem}
  input[type=range]{width:100%}
</style>
</head>
<body>
<h1>Kontrol LED ESP8266</h1>
<div class="card"><label>LED 1: <b id="v1">0</b>%</label>
<input type="range" min="0" max="100" value="0" id="s1"></div>
<div class="card"><label>LED 2: <b id="v2">0</b>%</label>
<input type="range" min="0" max="100" value="0" id="s2"></div>
<script>
let last = 0;
function send(n, v, force) {
  const t = Date.now();
  if (!force && t - last < 60) return;
  last = t;
  fetch('/set?led=' + n + '&val=' + v);
}
[1, 2].forEach(n => {
  const s = document.getElementById('s' + n);
  const l = document.getElementById('v' + n);
  s.oninput = () => { l.textContent = s.value; send(n, s.value, false); };
  s.onchange = () => send(n, s.value, true);
});
fetch('/state').then(r => r.json()).then(d => {
  [1, 2].forEach(n => {
    document.getElementById('s' + n).value = d['l' + n];
    document.getElementById('v' + n).textContent = d['l' + n];
  });
});
</script>
</body>
</html>
)rawliteral";

// Mata melihat kecerahan secara tidak linear, jadi persen dikuadratkan
// supaya geser slider terasa merata dari redup sampai terang.
void applyLevel(int i) {
  float f = level[i] / 100.0f;
  analogWrite(LED_PINS[i], (int)(f * f * 1023));
}

void handleRoot() {
  server.send_P(200, "text/html", PAGE);
}

void handleSet() {
  if (!server.hasArg("led") || !server.hasArg("val")) {
    server.send(400, "text/plain", "parameter led dan val wajib ada");
    return;
  }
  int led = server.arg("led").toInt();
  if (led < 1 || led > 2) {
    server.send(400, "text/plain", "led harus 1 atau 2");
    return;
  }
  level[led - 1] = constrain(server.arg("val").toInt(), 0, 100);
  applyLevel(led - 1);
  server.send(200, "text/plain", "ok");
}

void handleState() {
  String json = "{\"l1\":" + String(level[0]) + ",\"l2\":" + String(level[1]) + "}";
  server.send(200, "application/json", json);
}

void startWifi() {
  if (strlen(WIFI_SSID) > 0) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Menyambung ke ");
    Serial.print(WIFI_SSID);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
      delay(500);
      Serial.print('.');
    }
    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("Buka di browser: http://");
      Serial.println(WiFi.localIP());
      return;
    }
    Serial.println("Gagal tersambung, pindah ke mode Access Point.");
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  Serial.print("Sambungkan HP/laptop ke WiFi \"");
  Serial.print(AP_SSID);
  Serial.print("\" (password ");
  Serial.print(AP_PASSWORD);
  Serial.print("), lalu buka http://");
  Serial.println(WiFi.softAPIP());
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 2; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    applyLevel(i);
  }

  startWifi();

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.on("/state", handleState);
  server.begin();
  Serial.println("Web server jalan.");
}

void loop() {
  server.handleClient();
}
