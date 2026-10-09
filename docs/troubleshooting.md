# Troubleshooting

## Upload and connection

| Symptom | Cause and fix |
|---|---|
| Port not detected / `No serial port found` | Install the **CH340** driver, then unplug and replug. Try another USB cable, since many cables are charge-only. Check with `pio device list` |
| Fails at `Connecting......` | Hold the **FLASH** button on the board when the upload starts, and release it once progress begins |
| Garbled text in the Serial Monitor | Make sure the baud rate is **115200**. A few random characters at boot are normal (bootloader message) |
| "Configuring project" stuck at 50% | It is still downloading the toolchain, wait 5–15 minutes. Check the **Output** panel. If it is stuck, run `pio run` in a terminal to see the error |
| Red marks in the editor (`'Arduino.h' file not found`) | IntelliSense noise. If **Build** succeeds, ignore it. It usually goes away once PlatformIO finishes indexing or after one build |
| The uploaded environment is not the one you wanted | Check the environment name in the bottom status bar. Without `-e`, the terminal uses the default environment (`web_slider`) |

## LEDs

| Symptom | Cause and fix |
|---|---|
| One LED does not light up | Its + and − legs are swapped. Flip the LED around |
| Both LEDs are off | Check the wire to the **G** (GND) pin. Make sure the wires from the cathode rows go to the **blue (−)** rail |
| An LED does not react | Make sure the signal wires go to **D1** and **D2**, not SD1/SD2 |
| One LED is dimmer than the other | Different resistor values (check the color bands), different LEDs, or a loose contact. Swap the LEDs, then swap the resistors, to find the cause |
| LEDs are too dim | Do not connect several LEDs to one pin. One pin = one LED = one resistor |

Resistor color bands: 220 Ω = red-red-brown, 330 Ω = orange-orange-brown, 470 Ω = yellow-violet-brown.
Resistors have no direction, so they can be installed either way around.

## WiFi and web

| Symptom | Cause and fix |
|---|---|
| WiFi `ESP8266-LED` does not appear | Make sure a web example has **been uploaded** (building alone is not enough). Wait 5–10 seconds, then refresh the WiFi list or toggle WiFi off and on |
| Connected but the page does not open | Turn off **mobile data** on your phone. Use `http://`, not `https://`. The address is `http://192.168.4.1` |
| Cannot connect to home WiFi | Make sure the network is **2.4 GHz** and the SSID/password in `include/secrets.h` are correct. The ESP8266 falls back to Access Point mode after 15 seconds |
| Build fails: `secrets.h: No such file` | Copy `include/secrets.example.h` to `include/secrets.h` |

## Staying safe for the board

- Unplug USB before changing the circuit.
- The `A0` pin accepts 3.3 V at most.
- Never connect an LED without a resistor.
