# Change 0001: Initial modular LED firmware

## Summary

Create the first greenfield firmware implementation for the three target device variants.

## Added

- Shared application entry point.
- Board-family variant headers.
- Device IDs: `UNO-R4`, `XIAO-1`, and `XIAO-2`.
- Modular `led_status` feature.
- Five-second LED state-toggle interval.

## Affected devices

- Arduino UNO R4 WiFi.
- XIAO ESP32-S3 camera board 1.
- XIAO ESP32-S3 camera board 2.

## Verification

- Build each PlatformIO environment.
- Flash each board by USB.
- Confirm the onboard LED changes state every five seconds.

## OTA impact

None yet. OTA will be implemented only after this local build and hardware test succeeds.
