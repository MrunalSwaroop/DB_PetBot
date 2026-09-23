# Changelog

## Unreleased

### Added

- Arduino IDE-compatible baseline sketch using the original one-second blink behavior.
- Baseline target coverage for UNO R4 WiFi, two XIAO ESP32-S3 boards, NodeMCU ESP8266, and a generic ESP8266 module.
- Five-device hardware matrix and Arduino IDE setup notes.
- Initial UNO R4 WiFi OTA bootstrap service structure with local ignored Wi-Fi credentials.
- UNO bootstrap now persists Wi-Fi credentials locally after first USB provisioning.
- UNO R4 HTTPS OTA download, verification, and update path added for the first controlled test release.
- UNO R4 now checks a GitHub Pages manifest at startup and downloads only newer firmware versions.
- GitHub Actions now compiles, LZSS-compresses, packages, and publishes the UNO OTA artifact and manifest.
- XIAO ESP32-S3 backend added using Arduino ESP32 dual-slot raw-binary OTA and the shared GitHub Pages manifest pattern.
- CI now builds separate UNO `.ota` and XIAO `.bin` artifacts.

### Planned

- Per-device Wi-Fi provisioning.
- Per-device target selection in the deployment manifest.
- XIAO ESP32-S3 and ESP8266 OTA backends.
- Camera feature and external GPIO wiring.
- XIAO camera feature.
