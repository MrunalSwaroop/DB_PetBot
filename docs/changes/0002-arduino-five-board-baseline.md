# Change 0002: Arduino IDE five-board baseline

## Summary

Add an Arduino IDE-compatible baseline sketch using the user's original one-second blink code.

## Supported devices

- Arduino UNO R4 WiFi (`UNO-R4`)
- Seeed XIAO ESP32-S3 camera board 1 (`XIAO-1`)
- Seeed XIAO ESP32-S3 camera board 2 (`XIAO-2`)
- NodeMCU ESP8266 (`NODEMCU-1`)
- Generic ESP8266 module (`ESP8266-1`)

## Verification

Each board must be selected in Arduino IDE, compiled, flashed over USB, and observed for at least ten seconds. ESP8266 onboard LEDs may be active-low or may not be connected to `LED_BUILTIN` on a particular carrier board.

## OTA impact

This is still the USB baseline. Wi-Fi provisioning and OTA service are intentionally not included until this baseline is verified on the available boards.
