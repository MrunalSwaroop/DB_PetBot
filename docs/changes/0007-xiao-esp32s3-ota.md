# Change 0007: XIAO ESP32-S3 OTA backend

## Summary

Add a modular XIAO ESP32-S3 backend to the shared Friend Bot firmware. The backend uses the Arduino ESP32 Wi-Fi, `HTTPUpdate`, `WiFiClientSecure`, and `Preferences` libraries. It stores location-specific Wi-Fi credentials in NVS and performs HTTPS raw-binary OTA through the ESP32 dual-slot partition layout.

## Artifact format

The UNO R4 requires Arduino’s compressed `.ota` container. The XIAO ESP32-S3 receives the raw Arduino application `.bin` produced by the ESP32 core. These artifacts are published separately by GitHub Actions:

- `ota/UNO-R4.bin`: UNO R4 compressed `.ota` payload.
- `ota/XIAO-ESP32S3.bin`: XIAO ESP32-S3 raw application binary.
- `ota/xiao-esp32s3-manifest.json`: XIAO-specific version manifest.

## Hardware and partition requirements

The XIAO must use the `Seeed XIAO ESP32S3` board profile with 8 MB flash and the `Default with SPIFFS` partition scheme. This provides `ota_0` and `ota_1` slots. The `Maximum APP (No OTA/No FS)` scheme is intentionally excluded. The first OTA stage uses only the onboard LED and USB; no camera or external wiring is required.

## Verification

Compile with `esp32:esp32:XIAO_ESP32S3`, confirm the raw `.bin` is produced, verify the GitHub Actions build publishes the XIAO artifact and manifest, then upload the bootstrap over USB. The device must connect using stored credentials, report the manifest version, and update only when a newer version exists.

## Future hardening

Before production deployment, add signed firmware verification, per-device authorization, staged rollout controls, rollback policy, and a device registry that prevents the XIAO and UNO manifests from being confused.
