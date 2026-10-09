#pragma once

// Copy this file to secrets.h (same folder) and fill in your own values.
// secrets.h is listed in .gitignore, so your WiFi password is never committed.

// Home/dorm WiFi (2.4 GHz only, the ESP8266 does not support 5 GHz).
// Leave WIFI_SSID empty to use Access Point mode directly.
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// WiFi network created by the ESP8266 itself (Access Point mode).
// The password must be at least 8 characters.
#define AP_SSID "ESP8266-LED"
#define AP_PASSWORD "12345678"
