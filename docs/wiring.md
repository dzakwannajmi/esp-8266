# Rangkaian dan wiring

Semua contoh memakai dua LED. **Cabut USB sebelum memasang atau memindah kabel.**

## Komponen

- 1 NodeMCU ESP8266, 1 breadboard
- 2 LED, 2 resistor 220 Ω
- Jumper male-to-female (ke NodeMCU) dan male-to-male (di breadboard)

## Cara kerja breadboard

- Angka (1–60) adalah nomor baris. Lima lubang **a b c d e** dalam satu nomor saling terhubung. Begitu juga **f g h i j** di sisi kanan celah tengah. Sisi a–e dan f–j **tidak** terhubung.
- Rel di tepi (garis merah **+** dan biru **−**) terhubung memanjang. Pakai rel biru sebagai GND.
- Resistor tidak punya arah. **LED punya arah**: kaki panjang = anoda (+), kaki pendek = katoda (−). Kalau kaki sudah dipotong sama panjang, sisi **datar** di pinggiran lampu adalah katoda.

## Pin yang dipakai

| Fungsi | Pin NodeMCU | GPIO |
|---|---|---|
| LED 1 | D1 | 5 |
| LED 2 | D2 | 4 |
| Ground | G | – |
| Sensor LDR (opsional) | A0 | – |

## Alur sinyal

```
D1 → resistor 220Ω → LED 1 (+ → −) → rel GND → pin G
D2 → resistor 220Ω → LED 2 (+ → −) → rel GND → pin G
```

Satu pin = satu LED = satu resistor. Pin ESP8266 hanya aman memberi sekitar 12 mA, jadi jangan menyambung beberapa LED ke satu pin. Jangan pasang LED tanpa resistor.

## Langkah pemasangan

Nomor baris di bawah hanya contoh. Yang penting mengikuti aturan di bagian berikutnya.

1. Sambungkan pin **G** NodeMCU ke **rel biru (−)** dengan jumper male-to-female.
2. **LED 1** (baris 8–13):

   | Komponen | Posisi |
   |---|---|
   | Jumper dari **D1** | baris 8 (`b8`) |
   | Resistor, kaki 1 | baris 8 (`a8`) |
   | Resistor, kaki 2 | baris 12 (`a12`) |
   | LED 1, kaki panjang (+) | baris 12 (`b12`) |
   | LED 1, kaki pendek (−) | baris 13 (`b13`) |
   | Jumper dari baris 13 (`c13`) | ke rel biru (−) |

3. **LED 2**: pola sama, geser ke baris 18–23, jumper sinyal dari **D2**.
4. Periksa semua kaki masuk penuh dan tidak ada kaki yang bersentuhan, lalu colok USB.

### Aturan posisi

- Dua kaki satu komponen harus di **nomor baris yang berbeda**.
- Kaki resistor yang ke LED dan kaki panjang LED (+) harus di **nomor baris yang sama**.
- Set LED 1 dan LED 2 jangan berbagi nomor baris. Beri jarak 2–3 baris kosong.
- Resistor cukup berjarak 4–6 baris. LED cukup di dua baris bersebelahan.
- Kaki terlalu panjang: tekuk atau potong, sisakan 6–8 mm yang masuk lubang, supaya tidak menyentuh kaki lain.

## Modul LDR (contoh `ldr_auto`)

| Modul LDR | NodeMCU |
|---|---|
| VCC | 3V3 |
| GND | G |
| AO | A0 |

Pin `A0` hanya boleh menerima **0–3.3 V**. Jangan sambungkan ke 5 V.

## Batasan ESP8266 yang perlu diingat

- Hanya ada **satu pin analog** (`A0`).
- **D3, D4, D8** (GPIO 0, 2, 15) memengaruhi proses boot. Hindari untuk LED eksternal atau relay.
- Echo pin sensor **HC-SR04** keluar 5 V, sedangkan ESP8266 hanya toleran 3.3 V. Pakai pembagi tegangan.
- LCD I2C memakai **D1 (SCL)** dan **D2 (SDA)**, jadi bentrok dengan pin LED di proyek ini.
