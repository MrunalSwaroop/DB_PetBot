# Friend Bot Firmware

Greenfield modular firmware for one Arduino UNO R4 WiFi and two Seeed Studio XIAO ESP32-S3 camera boards.

## Current step

This first step contains only the modular onboard LED feature. Each board variant should toggle its onboard LED every five seconds.

OTA, Wi-Fi provisioning, camera support, and bot features will be added in later steps after this build is verified on hardware.

## Build locally

Install PlatformIO, then run:

```bash
pio run
```

The build matrix contains:

- `uno_r4`: Arduino UNO R4 WiFi, device ID `UNO-R4`
- `xiao_1`: XIAO ESP32-S3 camera board, device ID `XIAO-1`
- `xiao_2`: XIAO ESP32-S3 camera board, device ID `XIAO-2`

## Change tracking

- Current feature inventory: `docs/FEATURES.md`
- Hardware/device matrix: `docs/DEVICE_MATRIX.md`
- Release history: `docs/RELEASES.md`
- Human-readable changes: `CHANGELOG.md`
- Per-change notes: `docs/changes/`
