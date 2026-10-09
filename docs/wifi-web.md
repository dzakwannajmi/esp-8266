# Control over WiFi

The `web_slider` and `web_effects` examples run a small web server on the ESP8266. You control the LEDs from a browser on your phone or laptop.

Both are reachable only from the **same network** as the ESP8266 (not over the internet).

## Configuring `include/secrets.h`

Copy it from the template if it does not exist yet:

```bash
cp include/secrets.example.h include/secrets.h
```

| Setting | Purpose |
|---|---|
| `WIFI_SSID`, `WIFI_PASSWORD` | Home/dorm WiFi. Must be **2.4 GHz** |
| `AP_SSID`, `AP_PASSWORD` | WiFi network created by the ESP8266 itself. Password must be at least 8 characters |

`secrets.h` is in `.gitignore`, so your password is never committed.

## Two connection modes

### Access Point mode (default, no router needed)

Used when `WIFI_SSID` is **empty**, or when the ESP8266 fails to connect within 15 seconds.

1. Upload a web example and open the Serial Monitor.
2. On your phone or laptop, connect to the WiFi network **`ESP8266-LED`** (password `12345678`).
3. Open **`http://192.168.4.1`** in a browser.

This is the safest mode for experiments, especially on campus networks that block devices from talking to each other.

### Station mode (through your home/dorm WiFi)

1. Fill in `WIFI_SSID` and `WIFI_PASSWORD`, then upload again.
2. The Serial Monitor prints `Buka di browser: http://192.168.x.x`.
3. Open that address from a device connected to the same WiFi network.

## The web pages

- **`web_slider`**: two sliders (LED 1 and LED 2), 0–100%.
- **`web_effects`**: effect buttons (Off, On, Blink, Breathe, Swing) and one maximum-brightness slider.

## HTTP endpoints

Useful if you want to call the device from another app or `curl`.

**`web_slider`**

| Endpoint | Purpose |
|---|---|
| `GET /` | The web page |
| `GET /set?led=1&val=50` | Set LED 1 or 2 (`val` 0–100) |
| `GET /state` | Current state (JSON) |

**`web_effects`**

| Endpoint | Purpose |
|---|---|
| `GET /` | The web page |
| `GET /mode?m=napas` | Choose an effect: `mati`, `nyala`, `kedip`, `napas`, `ayunan` |
| `GET /bright?val=80` | Maximum brightness 0–100 |
| `GET /state` | Current state (JSON) |

The effect names are the Indonesian ones used in the code: `mati` = off, `nyala` = on, `kedip` = blink, `napas` = breathe, `ayunan` = swing.

Example:

```bash
curl "http://192.168.4.1/set?led=1&val=30"
```

## Security note

These endpoints have **no login**. Anyone on the same network can control the LEDs. That is fine for experiments, but do not use this as-is for anything important.
