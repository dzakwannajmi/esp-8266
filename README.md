# ESP8266 LED Lab

A collection of LED experiments for the NodeMCU ESP8266 using PlatformIO in VS Code: blinking, fading, SOS, a light sensor, and brightness control from a web page.

## Hardware

- NodeMCU ESP8266 (V3, CH340 USB chip)
- Breadboard and jumper wires
- 2 LEDs and 2 resistors (220 Ω)
- (optional) LDR module for the `ldr_auto` example

## Quick start

1. Install **VS Code** and the **PlatformIO IDE** extension.
2. Open this project folder (`File → Open Folder`) and wait for PlatformIO to finish downloading its tools.
3. Copy `include/secrets.example.h` to `include/secrets.h`.
4. Build the circuit as described in [docs/wiring.md](docs/wiring.md).
5. Pick an environment in the bottom status bar, then click **Upload**.

Or from the terminal:

```bash
pio run -e breathing_fade -t upload
pio device monitor
```

## Project structure

```
src/<number>_<name>/main.cpp   one folder = one example
include/secrets.example.h      WiFi template (copy to secrets.h)
platformio.ini                 list of environments
docs/                          full documentation
```

## Examples

| Environment | What it does |
|---|---|
| `alternate_blink` | LED 1 and LED 2 light up in turns |
| `sync_blink` | Both LEDs blink together |
| `breathing_fade` | Slow fade in and out, like breathing |
| `swing_fade` | LED 1 gets brighter as LED 2 gets dimmer |
| `sos` | SOS signal in Morse code |
| `candle` | Random flickering brightness, like a candle |
| `serial_control` | Control the LEDs from the Serial Monitor |
| `ldr_auto` | The darker it gets, the brighter the LED |
| `web_slider` | Brightness sliders in a browser |
| `web_effects` | Effect buttons and a slider in a browser |

## Documentation

- [Setup on another laptop](docs/setup.md)
- [Circuit and wiring](docs/wiring.md)
- [Example descriptions](docs/examples.md)
- [Control over WiFi](docs/wifi-web.md)
- [Troubleshooting](docs/troubleshooting.md)
