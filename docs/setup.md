# Setup on another laptop

How to run this project from scratch on a laptop that has never been used for Arduino or ESP8266 development.

## 1. Install the software

1. **VS Code**: https://code.visualstudio.com
2. In VS Code, open Extensions (`Cmd/Ctrl+Shift+X`), search for **PlatformIO IDE**, install it, then restart VS Code.
   The first launch downloads Python and PlatformIO's built-in tools. Wait until it finishes.
3. **CH340 USB driver** (the USB chip on the NodeMCU V3):
   - **macOS**: recent versions usually include it. If the port does not appear, install the CH340 driver from the manufacturer (WCH).
   - **Windows**: install the CH340 driver (WCH). The board then shows up as `COM3`, `COM4`, and so on.
   - **Linux**: no driver needed. Add your user to the `dialout` group and log in again:
     `sudo usermod -aG dialout $USER`

> The ESP8266 platform and libraries are downloaded automatically by PlatformIO from `platformio.ini`.
> The Arduino IDE URL (`package_esp8266com_index.json`) is **not used** here.

## 2. Get the project

Copy this project folder to the new laptop (USB drive, zip, or `git clone`).

You do not need to copy the `.pio/` folder. It is recreated automatically on the first build.

## 3. Create `secrets.h`

`include/secrets.h` is intentionally not tracked by Git because it holds your WiFi password. Create it from the template:

```bash
cp include/secrets.example.h include/secrets.h
```

Fill in `WIFI_SSID` and `WIFI_PASSWORD` to connect to your home WiFi, or leave them empty to use Access Point mode. Details are in [wifi-web.md](wifi-web.md).

## 4. Open the project

1. `File → Open Folder` and choose the project folder (the one containing `platformio.ini`).
2. Wait until the bottom status bar shows the PlatformIO icons (check mark, arrow, plug). The first open can take 5–15 minutes because the ESP8266 toolchain is downloaded.

## 5. Upload

1. Build the circuit as described in [wiring.md](wiring.md), then plug the NodeMCU in over USB. **Unplug USB before changing the circuit.**
2. In the bottom status bar, click the environment name (for example `env:web_slider`) and pick the example you want to try.
3. Click the arrow icon (**Upload**). On success the terminal shows `[SUCCESS]`.
4. Click the plug icon (**Serial Monitor**) to see the output, baud rate 115200.

## From the terminal (optional)

Run these in the project folder, using the PlatformIO terminal (`PlatformIO: New Terminal`) or after `pip install platformio`:

```bash
pio run -e web_slider              # build only
pio run -e web_slider -t upload    # build + upload
pio device list                    # list detected ports
pio device monitor                 # serial monitor
```

The list of environments is in [examples.md](examples.md).
