# Circuit and wiring

All examples use two LEDs. **Unplug USB before adding or moving wires.**

## Parts

- 1 NodeMCU ESP8266, 1 breadboard
- 2 LEDs, 2 resistors (220 Ω)
- Male-to-female jumpers (to the NodeMCU) and male-to-male jumpers (on the breadboard)

## How the breadboard works

- The numbers (1–60) are row numbers. The five holes **a b c d e** in one row are connected to each other, and so are **f g h i j** on the other side of the center gap. The a–e side and the f–j side are **not** connected.
- The rails along the edges (red **+** and blue **−** lines) are connected along their whole length. Use the blue rail as GND.
- Resistors have no direction. **LEDs do**: the long leg is the anode (+) and the short leg is the cathode (−). If the legs have been trimmed to the same length, the **flat** side on the rim of the LED is the cathode.

## Pins used

| Function | NodeMCU pin | GPIO |
|---|---|---|
| LED 1 | D1 | 5 |
| LED 2 | D2 | 4 |
| Ground | G | – |
| LDR sensor (optional) | A0 | – |

## Signal path

```
D1 → 220Ω resistor → LED 1 (+ → −) → GND rail → G pin
D2 → 220Ω resistor → LED 2 (+ → −) → GND rail → G pin
```

One pin = one LED = one resistor. An ESP8266 pin can safely supply only about 12 mA, so do not connect several LEDs to one pin. Never connect an LED without a resistor.

## Assembly steps

The row numbers below are only an example. What matters is following the rules in the next section.

1. Connect the **G** pin on the NodeMCU to the **blue rail (−)** with a male-to-female jumper.
2. **LED 1** (rows 8–13):

   | Part | Position |
   |---|---|
   | Jumper from **D1** | row 8 (`b8`) |
   | Resistor, leg 1 | row 8 (`a8`) |
   | Resistor, leg 2 | row 12 (`a12`) |
   | LED 1, long leg (+) | row 12 (`b12`) |
   | LED 1, short leg (−) | row 13 (`b13`) |
   | Jumper from row 13 (`c13`) | to the blue rail (−) |

3. **LED 2**: same pattern, shifted to rows 18–23, with the signal jumper from **D2**.
4. Check that every leg is fully inserted and no legs touch each other, then plug in USB.

### Placement rules

- The two legs of one component must be in **different row numbers**.
- The resistor leg that goes to the LED and the LED's long leg (+) must be in the **same row number**.
- LED 1 and LED 2 must not share row numbers. Leave 2–3 empty rows between them.
- A resistor only needs to span 4–6 rows. An LED only needs two neighboring rows.
- If a leg is too long, bend or trim it so that 6–8 mm goes into the hole and it cannot touch other legs.

## LDR module (`ldr_auto` example)

| LDR module | NodeMCU |
|---|---|
| VCC | 3V3 |
| GND | G |
| AO | A0 |

The `A0` pin only accepts **0–3.3 V**. Never connect it to 5 V.

## ESP8266 limitations to keep in mind

- There is only **one analog pin** (`A0`).
- **D3, D4, D8** (GPIO 0, 2, 15) affect the boot process. Avoid them for external LEDs or relays.
- The echo pin of an **HC-SR04** outputs 5 V, but the ESP8266 only tolerates 3.3 V. Use a voltage divider.
- An I2C LCD uses **D1 (SCL)** and **D2 (SDA)**, which clash with the LED pins in this project.
