# Kontrol lewat WiFi

Contoh `web_slider` dan `web_effects` menjalankan web server kecil di ESP8266. LED dikontrol dari browser HP atau laptop.

Keduanya hanya bisa diakses dari **jaringan yang sama** dengan ESP8266 (tidak lewat internet).

## Mengatur `include/secrets.h`

Salin dari template kalau belum ada:

```bash
cp include/secrets.example.h include/secrets.h
```

| Isi | Fungsi |
|---|---|
| `WIFI_SSID`, `WIFI_PASSWORD` | WiFi rumah/kos. Harus **2.4 GHz** |
| `AP_SSID`, `AP_PASSWORD` | WiFi buatan ESP8266 sendiri. Password minimal 8 karakter |

`secrets.h` ada di `.gitignore`, jadi password tidak ikut ter-commit.

## Dua mode sambungan

### Mode Access Point (default, tanpa router)

Dipakai kalau `WIFI_SSID` **kosong**, atau kalau ESP8266 gagal tersambung dalam 15 detik.

1. Upload contoh web, buka Serial Monitor.
2. Di HP/laptop, sambungkan ke WiFi **`ESP8266-LED`** (password `12345678`).
3. Buka **`http://192.168.4.1`** di browser.

Mode ini paling aman untuk percobaan, apalagi di kampus yang WiFi-nya memblokir komunikasi antar perangkat.

### Mode Station (lewat WiFi rumah/kos)

1. Isi `WIFI_SSID` dan `WIFI_PASSWORD`, lalu upload ulang.
2. Serial Monitor menampilkan `Buka di browser: http://192.168.x.x`.
3. Buka alamat itu dari perangkat yang tersambung ke WiFi yang sama.

## Halaman web

- **`web_slider`**: dua slider (LED 1 dan LED 2), 0–100%.
- **`web_effects`**: tombol efek (Mati, Nyala, Kedip, Napas, Ayunan) dan satu slider kecerahan maksimum.

## Endpoint HTTP

Berguna kalau mau memanggil dari aplikasi lain atau `curl`.

**`web_slider`**

| Endpoint | Fungsi |
|---|---|
| `GET /` | Halaman web |
| `GET /set?led=1&val=50` | Atur LED 1 atau 2 (`val` 0–100) |
| `GET /state` | Status sekarang (JSON) |

**`web_effects`**

| Endpoint | Fungsi |
|---|---|
| `GET /` | Halaman web |
| `GET /mode?m=napas` | Pilih efek: `mati`, `nyala`, `kedip`, `napas`, `ayunan` |
| `GET /bright?val=80` | Kecerahan maksimum 0–100 |
| `GET /state` | Status sekarang (JSON) |

Contoh:

```bash
curl "http://192.168.4.1/set?led=1&val=30"
```

## Catatan keamanan

Endpoint ini **tidak memakai login**. Siapa pun di jaringan yang sama bisa mengontrol LED. Cukup untuk percobaan, jangan dipakai apa adanya untuk perangkat penting.
