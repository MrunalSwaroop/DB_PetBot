# DB_PetBot

Desktop Bot Main file and modular Arduino firmware.

## Current firmware step

The Arduino IDE baseline is in `firmware/friend_bot/friend_bot.ino`. It preserves the original blink sketch: onboard LED HIGH for one second and LOW for one second.

The planned device matrix is:

- Arduino UNO R4 WiFi (`UNO-R4`)
- XIAO ESP32-S3 camera board 1 (`XIAO-1`)
- XIAO ESP32-S3 camera board 2 (`XIAO-2`)
- NodeMCU ESP8266 (`NODEMCU-1`)
- Generic ESP8266 module (`ESP8266-1`)

Open the `.ino` file in Arduino IDE for the first USB test. Wi-Fi provisioning and OTA will be added only after the baseline is verified on the available boards.

## Repository tracking

- Hardware matrix: `docs/DEVICE_MATRIX.md`
- Feature inventory: `docs/FEATURES.md`
- Release history: `docs/RELEASES.md`
- Deployment history: `docs/DEPLOYMENT_LOG.md`
- Human-readable changes: `CHANGELOG.md`
- Per-change notes: `docs/changes/`

Do not commit Wi-Fi passwords, API keys, signing keys, or other secrets.

## Repository history

The original repository README was preserved during the firmware project merge. Future firmware changes should follow `CONTRIBUTING.md` and remain modular under `src/features/`.
