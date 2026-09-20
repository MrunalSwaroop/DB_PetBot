# Changelog

## Unreleased

### Added

- Arduino IDE-compatible baseline sketch using the original one-second blink behavior.
- Baseline target coverage for UNO R4 WiFi, two XIAO ESP32-S3 boards, NodeMCU ESP8266, and a generic ESP8266 module.
- Five-device hardware matrix and Arduino IDE setup notes.
- Initial UNO R4 WiFi OTA bootstrap service structure with local ignored Wi-Fi credentials.
- UNO bootstrap now persists Wi-Fi credentials locally after first USB provisioning.

### Planned

- Per-device Wi-Fi provisioning.
- HTTPS pull-based OTA updates.
- GitHub Actions Arduino CLI build and manually targeted deployments.
- XIAO camera feature.
