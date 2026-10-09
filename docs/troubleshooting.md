# Troubleshooting

## Upload dan koneksi

| Gejala | Penyebab dan solusi |
|---|---|
| Port tidak terdeteksi / `No serial port found` | Install driver **CH340**, cabut lalu colok ulang. Coba kabel USB lain, karena banyak kabel hanya untuk charging. Cek dengan `pio device list` |
| Gagal di `Connecting......` | Tahan tombol **FLASH** di board saat upload dimulai, lepas setelah progress jalan |
| Teks aneh di Serial Monitor | Pastikan baud rate **115200**. Beberapa baris acak saat boot itu normal (pesan bootloader) |
| Configuring project lama di 50% | Masih mengunduh toolchain, tunggu 5–15 menit. Cek panel **Output**. Kalau macet, jalankan `pio run` di terminal untuk melihat error |
| Ada tanda merah di editor (`'Arduino.h' file not found`) | Noise IntelliSense. Kalau **Build** berhasil, abaikan. Biasanya hilang setelah PlatformIO selesai indexing atau setelah build sekali |
| Environment yang di-upload tidak sesuai | Cek nama environment di status bar bawah. Tanpa `-e`, terminal memakai environment default (`web_slider`) |

## LED

| Gejala | Penyebab dan solusi |
|---|---|
| Satu LED tidak menyala | Kaki + dan − tertukar. Balik arah LED |
| Dua-duanya mati | Cek kabel ke pin **G** (GND). Pastikan kabel dari baris katoda masuk ke rel **biru (−)** |
| LED tidak bereaksi | Pastikan kabel sinyal ke **D1** dan **D2**, bukan SD1/SD2 |
| Salah satu LED lebih redup | Nilai resistor berbeda (cek gelang warna), LED berbeda, atau kontak longgar. Tukar posisi LED, lalu tukar resistor, untuk mencari penyebabnya |
| LED terlalu redup | Jangan sambung beberapa LED ke satu pin. Satu pin = satu LED = satu resistor |

Gelang warna resistor: 220 Ω = merah-merah-coklat, 330 Ω = oranye-oranye-coklat, 470 Ω = kuning-ungu-coklat.
Resistor tidak punya arah, boleh dipasang terbalik.

## WiFi dan web

| Gejala | Penyebab dan solusi |
|---|---|
| WiFi `ESP8266-LED` tidak muncul | Pastikan kode contoh web **sudah di-upload** (build saja tidak cukup). Tunggu 5–10 detik, lalu refresh daftar WiFi atau matikan-nyalakan WiFi |
| Tersambung tapi halaman tidak terbuka | Matikan **data seluler** di HP. Pakai `http://`, bukan `https://`. Alamat: `http://192.168.4.1` |
| Gagal tersambung ke WiFi rumah | Pastikan WiFi **2.4 GHz** dan SSID/password di `include/secrets.h` benar. ESP8266 otomatis pindah ke mode Access Point setelah 15 detik |
| Build gagal: `secrets.h: No such file` | Salin `include/secrets.example.h` menjadi `include/secrets.h` |

## Aman untuk board

- Cabut USB sebelum mengubah rangkaian.
- Pin `A0` maksimal 3.3 V.
- Jangan memasang LED tanpa resistor.
