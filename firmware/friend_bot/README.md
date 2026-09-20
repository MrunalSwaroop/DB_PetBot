# Friend Bot Arduino IDE firmware

This is the simple USB-test baseline. It preserves the original Arduino blink sketch: the onboard LED is driven HIGH for one second and LOW for one second.

## Supported Arduino IDE board selections

| Device | Arduino IDE board selection | Expected LED behavior |
|---|---|---|
| UNO-R4 | Arduino UNO R4 WiFi | 1 second HIGH, 1 second LOW |
| XIAO-1 | Seeed XIAO ESP32-S3 | 1 second HIGH, 1 second LOW; polarity may be inverted |
| XIAO-2 | Seeed XIAO ESP32-S3 | 1 second HIGH, 1 second LOW; polarity may be inverted |
| NODEMCU-1 | NodeMCU 1.0 (ESP-12E Module) | 1 second HIGH, 1 second LOW; onboard LED may be inverted |
| ESP8266-1 | Generic ESP8266 Module | 1 second HIGH, 1 second LOW; module LED/pin depends on the carrier board |

The exact ESP8266 module profile must be confirmed before flashing. A bare ESP-01 normally requires a USB-to-serial adapter and correct 3.3 V power.

## USB upload

Open `friend_bot.ino` in Arduino IDE. Install the board package required by the selected board, choose the board and serial port, then use **Upload**.

This baseline does not contain Wi-Fi or OTA code yet. Do not move a board to a remote location until the later OTA bootstrap has been installed and tested.
