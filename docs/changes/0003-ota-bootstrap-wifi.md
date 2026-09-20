# Change 0003: OTA bootstrap Wi-Fi service

## Summary

Add the permanent OTA service structure while preserving the Arduino IDE application workflow and one-second LED behavior.

## Current behavior

The UNO R4 WiFi build can read locally supplied Wi-Fi credentials from an ignored `secrets.h`, connect to the local Wi-Fi network, and report its IP address over Serial. It does not download firmware yet.

## Affected devices

The initial backend is enabled only for `UNO-R4`. XIAO and ESP8266 backends will be added after the UNO connectivity step is verified.

## Security

Wi-Fi credentials are excluded from Git by `.gitignore`. No credentials belong in the repository, release artifacts, or CI logs.

## Verification

Upload the sketch by USB to the UNO, open Serial Monitor at 115200 baud, confirm Wi-Fi connection and IP address, and confirm the LED continues toggling every second.
