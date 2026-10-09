# Penjelasan contoh

Setiap contoh ada di `src/<nomor>_<nama>/main.cpp` dan dipilih lewat environment di `platformio.ini`.

Pilih lewat status bar VS Code, atau:

```bash
pio run -e <environment> -t upload
```

Semua contoh memakai **D1 (LED 1)** dan **D2 (LED 2)**, kecuali disebut lain. Wiring ada di [wiring.md](wiring.md).

| Environment | Folder | Perilaku |
|---|---|---|
| `alternate_blink` | `01_alternate_blink` | LED 1 dan 2 menyala bergantian tiap 0,5 detik |
| `sync_blink` | `02_sync_blink` | Kedua LED hidup-mati bersamaan. Ubah `JEDA` untuk kecepatan |
| `breathing_fade` | `03_breathing_fade` | Kedua LED terang-redup pelan (fade in/out) |
| `swing_fade` | `04_swing_fade` | LED 1 makin terang saat LED 2 makin redup, lalu sebaliknya |
| `sos` | `05_sos` | Sinyal SOS morse (`...---...`) diulang terus |
| `candle` | `06_candle` | Kecerahan acak, tiap LED sendiri-sendiri |
| `serial_control` | `07_serial_control` | Kontrol lewat Serial Monitor (lihat di bawah) |
| `ldr_auto` | `08_ldr_auto` | Makin gelap, LED 1 makin terang. LED 2 menyala saat sangat gelap |
| `web_slider` | `09_web_slider` | Slider kecerahan di halaman web ([wifi-web.md](wifi-web.md)) |
| `web_effects` | `10_web_effects` | Tombol efek dan slider di halaman web ([wifi-web.md](wifi-web.md)) |

## Tentang PWM dan kecerahan

Di ESP8266, `analogWrite(pin, nilai)` bernilai **0 (mati) sampai 1023 (terang penuh)**. Nilai kecil membuat LED lebih sering mati sehingga tampak redup.

Mata melihat kecerahan secara tidak linear. Karena itu contoh fade dan web memakai nilai yang **dikuadratkan** (gamma) supaya perubahan terasa merata.

## `serial_control`

Buka Serial Monitor (115200 baud), ketik perintah lalu tekan Enter:

| Perintah | Hasil |
|---|---|
| `1 50` | LED 1 kecerahan 50% |
| `2 100` | LED 2 kecerahan 100% |
| `on` | Kedua LED 100% |
| `off` | Kedua LED mati |
| `help` | Tampilkan bantuan |

## `ldr_auto`

- Sambungkan modul LDR ke `A0` ([wiring.md](wiring.md)).
- Buka Serial Monitor untuk melihat nilai sensor.
- Kalau LED malah menyala saat terang, ubah `GELAP_NILAI_TINGGI` menjadi `true` di `main.cpp`. Arah nilai tiap modul LDR berbeda.
- `AMBANG_GELAP` mengatur batas gelap untuk menyalakan LED 2.

## Menambah contoh baru

1. Buat folder `src/11_nama_contoh/main.cpp`.
2. Tambahkan environment di `platformio.ini`:

   ```ini
   [env:nama_contoh]
   build_src_filter = -<*> +<11_nama_contoh/>
   ```
