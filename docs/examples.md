# Example descriptions

Each example lives in `src/<number>_<name>/main.cpp` and is selected through an environment in `platformio.ini`.

Pick one from the VS Code status bar, or run:

```bash
pio run -e <environment> -t upload
```

All examples use **D1 (LED 1)** and **D2 (LED 2)** unless noted otherwise. Wiring is in [wiring.md](wiring.md).

| Environment | Folder | Behavior |
|---|---|---|
| `alternate_blink` | `01_alternate_blink` | LED 1 and LED 2 light up in turns every 0.5 s |
| `sync_blink` | `02_sync_blink` | Both LEDs turn on and off together. Change `JEDA` to set the speed |
| `breathing_fade` | `03_breathing_fade` | Both LEDs slowly fade in and out |
| `swing_fade` | `04_swing_fade` | LED 1 gets brighter while LED 2 gets dimmer, then the reverse |
| `sos` | `05_sos` | SOS signal in Morse code (`...---...`), repeated |
| `candle` | `06_candle` | Random brightness, each LED on its own |
| `serial_control` | `07_serial_control` | Control from the Serial Monitor (see below) |
| `ldr_auto` | `08_ldr_auto` | The darker it gets, the brighter LED 1. LED 2 turns on when it is very dark |
| `web_slider` | `09_web_slider` | Brightness sliders on a web page ([wifi-web.md](wifi-web.md)) |
| `web_effects` | `10_web_effects` | Effect buttons and a slider on a web page ([wifi-web.md](wifi-web.md)) |

## About PWM and brightness

On the ESP8266, `analogWrite(pin, value)` takes a value from **0 (off) to 1023 (full brightness)**. A small value keeps the LED off most of the time, so it looks dim.

The eye perceives brightness non-linearly, so the fade and web examples **square** the value (gamma correction) to make changes look even.

## `serial_control`

Open the Serial Monitor (115200 baud), type a command, and press Enter:

| Command | Result |
|---|---|
| `1 50` | LED 1 at 50% brightness |
| `2 100` | LED 2 at 100% brightness |
| `on` | Both LEDs at 100% |
| `off` | Both LEDs off |
| `help` | Show help |

## `ldr_auto`

- Connect the LDR module to `A0` ([wiring.md](wiring.md)).
- Open the Serial Monitor to see the sensor values.
- If the LED lights up in bright light instead, set `GELAP_NILAI_TINGGI` to `true` in `main.cpp`. The direction of the value differs between LDR modules.
- `AMBANG_GELAP` sets the darkness threshold that turns LED 2 on.

## Adding a new example

1. Create `src/11_example_name/main.cpp`.
2. Add an environment to `platformio.ini`:

   ```ini
   [env:example_name]
   build_src_filter = -<*> +<11_example_name/>
   ```
