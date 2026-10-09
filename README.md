# ESP8266 LED Lab

Kumpulan percobaan LED untuk NodeMCU ESP8266 memakai PlatformIO di VS Code: kedip, fade, SOS, sensor cahaya, sampai kontrol kecerahan lewat halaman web.

## Hardware

- NodeMCU ESP8266 (V3, chip USB CH340)
- Breadboard, kabel jumper
- 2 LED + 2 resistor 220 Ω
- (opsional) modul LDR untuk contoh `ldr_auto`

## Mulai cepat

1. Install **VS Code** dan extension **PlatformIO IDE**.
2. Buka folder project ini (`File → Open Folder`), tunggu PlatformIO selesai mengunduh.
3. Salin `include/secrets.example.h` menjadi `include/secrets.h`.
4. Rakit rangkaian sesuai [docs/wiring.md](docs/wiring.md).
5. Pilih environment di status bar bawah, lalu klik **Upload**.

Atau lewat terminal:

```bash
pio run -e breathing_fade -t upload
pio device monitor
```

## Struktur

```
src/<nomor>_<nama>/main.cpp   satu folder = satu contoh
include/secrets.example.h     template WiFi (salin ke secrets.h)
platformio.ini                daftar environment
docs/                         dokumentasi lengkap
```

## Contoh yang tersedia

| Environment | Isi |
|---|---|
| `alternate_blink` | LED 1 dan 2 menyala bergantian |
| `sync_blink` | Kedua LED kedip bersamaan |
| `breathing_fade` | Terang-redup pelan seperti bernapas |
| `swing_fade` | LED 1 makin terang, LED 2 makin redup |
| `sos` | Sinyal SOS morse |
| `candle` | Kecerahan acak seperti api lilin |
| `serial_control` | Kontrol lewat Serial Monitor |
| `ldr_auto` | Makin gelap, LED makin terang |
| `web_slider` | Slider kecerahan lewat browser |
| `web_effects` | Tombol efek dan slider lewat browser |

## Dokumentasi

- [Setup di laptop lain](docs/setup.md)
- [Rangkaian dan wiring](docs/wiring.md)
- [Penjelasan tiap contoh](docs/examples.md)
- [Kontrol lewat WiFi](docs/wifi-web.md)
- [Troubleshooting](docs/troubleshooting.md)
