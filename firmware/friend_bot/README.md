# Friend Bot Arduino IDE firmware

This is the modular Arduino IDE firmware base. It preserves the original Arduino blink sketch: the onboard LED is driven HIGH for one second and LOW for one second. UNO R4 WiFi and XIAO ESP32-S3 have HTTPS manifest-driven OTA backends; the other boards remain USB-only until their backends are added.

## Supported Arduino IDE board selections

| Device | Arduino IDE board selection | Expected LED behavior |
|---|---|---|
| UNO-R4 | Arduino UNO R4 WiFi | 1 second HIGH, 1 second LOW |
| XIAO-1 | Seeed XIAO ESP32-S3 | 2.5 seconds HIGH, 2.5 seconds LOW; 5-second complete cycle; polarity may be inverted |
| XIAO-2 | Seeed XIAO ESP32-S3 | 2.5 seconds HIGH, 2.5 seconds LOW; 5-second complete cycle; polarity may be inverted |
| NODEMCU-1 | NodeMCU 1.0 (ESP-12E Module) | 1 second HIGH, 1 second LOW; onboard LED may be inverted |
| ESP8266-1 | Generic ESP8266 Module | 1 second HIGH, 1 second LOW; module LED/pin depends on the carrier board |

The exact ESP8266 module profile must be confirmed before flashing. A bare ESP-01 normally requires a USB-to-serial adapter and correct 3.3 V power.

## USB upload

Open `friend_bot.ino` in Arduino IDE. Install the board package required by the selected board, choose the board and serial port, then use **Upload**.

Do not move a board to a remote location until its Wi-Fi credentials and OTA bootstrap have been installed and tested.

## XIAO ESP32-S3 OTA prerequisites

Install the Espressif ESP32 board package and select `Seeed XIAO ESP32S3`. Keep the board’s flash size at `8MB` and select the `Default with SPIFFS` partition scheme. This scheme provides two OTA application slots; do not select `Maximum APP (No OTA/No FS)` for a remotely updated board.

Copy `ota_target.xiao.example.h` to the ignored local file `ota_target.h`, add the local Wi-Fi credentials in `secrets.h`, and upload the first bootstrap over USB. No external circuit is required for this stage: the onboard LED and USB connection are sufficient. The camera module is not initialized yet, so no camera wiring or GPIO changes are introduced by the OTA base.
