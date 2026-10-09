#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "secrets.h"

// Halaman web dengan tombol efek (Mati, Nyala, Kedip, Napas, Ayunan)
// dan slider kecerahan maksimum. Cara sambung WiFi sama dengan 09_web_slider.

enum Mode { MATI, NYALA, KEDIP, NAPAS, AYUNAN };

const int LED_PINS[2] = {D1, D2};
Mode mode = MATI;
int kecerahan = 100;  // persen, 0-100
unsigned long terakhirUpdate = 0;

ESP8266WebServer server(80);

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Efek LED</title>
<style>
  body{font-family:system-ui,sans-serif;max-width:420px;margin:2rem auto;padding:0 1rem}
  h1{font-size:1.3rem}
  .grid{display:grid;grid-template-columns:repeat(2,1fr);gap:.6rem;margin-bottom:1.2rem}
  button{padding:.9rem;font-size:1rem;border-radius:10px;border:1px solid #888;background:#f4f4f4;cursor:pointer}
  button.aktif{background:#222;color:#fff}
  input[type=range]{width:100%}
</style>
</head>
<body>
<h1>Efek LED ESP8266</h1>
<div class="grid" id="grid"></div>
<label>Kecerahan maksimum: <b id="v">100</b>%</label>
<input type="range" min="0" max="100" value="100" id="s">
<script>
const efek = ['mati', 'nyala', 'kedip', 'napas', 'ayunan'];
const grid = document.getElementById('grid');
efek.forEach(e => {
  const b = document.createElement('button');
  b.textContent = e.charAt(0).toUpperCase() + e.slice(1);
  b.id = 'b-' + e;
  b.onclick = () => { fetch('/mode?m=' + e).then(tampil); };
  grid.appendChild(b);
});
function tampil() {
  fetch('/state').then(r => r.json()).then(d => {
    efek.forEach(e => document.getElementById('b-' + e).className = d.mode === e ? 'aktif' : '');
    document.getElementById('s').value = d.kecerahan;
    document.getElementById('v').textContent = d.kecerahan;
  });
}
let last = 0;
const s = document.getElementById('s');
const v = document.getElementById('v');
s.oninput = () => {
  v.textContent = s.value;
  const t = Date.now();
  if (t - last < 60) return;
  last = t;
  fetch('/bright?val=' + s.value);
};
s.onchange = () => fetch('/bright?val=' + s.value);
tampil();
</script>
</body>
</html>
)rawliteral";

const char* NAMA_MODE[] = {"mati", "nyala", "kedip", "napas", "ayunan"};

// Persen (0-100) -> nilai PWM 0-1023, dikuadratkan agar terasa merata di mata.
int duty(float persen) {
  float f = persen / 100.0f;
  return (int)(f * f * 1023);
}

void setLeds(float p1, float p2) {
  analogWrite(LED_PINS[0], duty(p1));
  analogWrite(LED_PINS[1], duty(p2));
}

void handleRoot() {
  server.send_P(200, "text/html", PAGE);
}

void handleMode() {
  String m = server.arg("m");
  for (int i = 0; i < 5; i++) {
    if (m == NAMA_MODE[i]) {
      mode = (Mode)i;
      server.send(200, "text/plain", "ok");
      return;
    }
  }
  server.send(400, "text/plain", "mode tidak dikenal");
}

void handleBright() {
  if (!server.hasArg("val")) {
    server.send(400, "text/plain", "parameter val wajib ada");
    return;
  }
  kecerahan = constrain(server.arg("val").toInt(), 0, 100);
  server.send(200, "text/plain", "ok");
}

void handleState() {
  String json = "{\"mode\":\"" + String(NAMA_MODE[mode]) + "\",\"kecerahan\":" + String(kecerahan) + "}";
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
  pinMode(LED_PINS[0], OUTPUT);
  pinMode(LED_PINS[1], OUTPUT);
  setLeds(0, 0);

  startWifi();

  server.on("/", handleRoot);
  server.on("/mode", handleMode);
  server.on("/bright", handleBright);
  server.on("/state", handleState);
  server.begin();
  Serial.println("Web server jalan.");
}

void loop() {
  server.handleClient();

  unsigned long now = millis();
  if (now - terakhirUpdate < 10) return;
  terakhirUpdate = now;

  // Gelombang segitiga 0..1 dengan periode 2 detik, untuk efek napas dan ayunan.
  float fase = (now % 2000) / 2000.0f;
  float segitiga = fase < 0.5f ? fase * 2 : 2 - fase * 2;

  switch (mode) {
    case MATI:
      setLeds(0, 0);
      break;
    case NYALA:
      setLeds(kecerahan, kecerahan);
      break;
    case KEDIP: {
      bool hidup = (now / 500) % 2 == 0;
      float p = hidup ? kecerahan : 0;
      setLeds(p, p);
      break;
    }
    case NAPAS:
      setLeds(segitiga * kecerahan, segitiga * kecerahan);
      break;
    case AYUNAN:
      setLeds(segitiga * kecerahan, (1 - segitiga) * kecerahan);
      break;
  }
}
