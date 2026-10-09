# Setup di laptop lain

Panduan untuk menjalankan project ini dari nol di laptop yang belum pernah dipakai untuk Arduino/ESP8266.

## 1. Install software

1. **VS Code**: https://code.visualstudio.com
2. Di VS Code, buka Extensions (`Cmd/Ctrl+Shift+X`), cari **PlatformIO IDE**, install, lalu restart VS Code.
   Pertama kali dibuka, PlatformIO mengunduh Python dan tool bawaannya. Tunggu sampai selesai.
3. **Driver USB CH340** (chip USB pada NodeMCU V3):
   - **macOS** terbaru biasanya sudah bawaan. Kalau port tidak muncul, install driver CH340 dari produsen (WCH).
   - **Windows**: install driver CH340 (WCH). Setelah itu port muncul sebagai `COM3`, `COM4`, dst.
   - **Linux**: tidak perlu driver. Tambahkan user ke grup `dialout`, lalu login ulang:
     `sudo usermod -aG dialout $USER`

> Platform ESP8266 dan library diunduh otomatis oleh PlatformIO dari `platformio.ini`.
> URL `package_esp8266com_index.json` milik Arduino IDE **tidak dipakai** di sini.

## 2. Ambil project

Salin folder project ini ke laptop baru (flashdisk, zip, atau `git clone` kalau sudah diunggah ke Git).

Folder `.pio/` tidak perlu disalin. Folder itu dibuat ulang otomatis saat build.

## 3. Buat file `secrets.h`

File `include/secrets.h` sengaja tidak ikut Git karena berisi password WiFi. Buat dari template:

```bash
cp include/secrets.example.h include/secrets.h
```

Isi `WIFI_SSID` dan `WIFI_PASSWORD` kalau mau tersambung ke WiFi rumah. Kosongkan kalau mau memakai mode Access Point. Detailnya di [wifi-web.md](wifi-web.md).

## 4. Buka project

1. `File → Open Folder`, pilih folder project (yang berisi `platformio.ini`).
2. Tunggu status bar bawah menampilkan ikon PlatformIO (centang, panah, colokan). Pembukaan pertama bisa 5–15 menit karena mengunduh toolchain ESP8266.

## 5. Upload

1. Rakit rangkaian sesuai [wiring.md](wiring.md), lalu colok NodeMCU lewat USB. **Cabut USB sebelum mengubah rangkaian.**
2. Di status bar bawah, klik nama environment (mis. `env:web_slider`) lalu pilih contoh yang mau dicoba.
3. Klik ikon panah (**Upload**). Kalau berhasil, terminal menampilkan `[SUCCESS]`.
4. Klik ikon colokan (**Serial Monitor**) untuk melihat output, baud rate 115200.

## Lewat terminal (opsional)

Jalankan di folder project, memakai terminal PlatformIO (`PlatformIO: New Terminal`) atau setelah `pip install platformio`:

```bash
pio run -e web_slider              # build saja
pio run -e web_slider -t upload    # build + upload
pio device list                    # cek port yang terdeteksi
pio device monitor                 # serial monitor
```

Daftar environment ada di [examples.md](examples.md).
