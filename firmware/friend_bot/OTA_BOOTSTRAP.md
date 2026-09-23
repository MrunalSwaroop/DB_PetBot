# OTA bootstrap: current step

The bootstrap now has the first direct HTTPS OTA download path, but the first controlled update must be tested before the general per-device manifest workflow is enabled. It also stores the UNO R4 WiFi credentials locally after the first USB setup.

## Local setup

1. Copy `secrets.example.h` to `secrets.h` in this same folder.
2. Replace `WIFI_SSID` and `WIFI_PASSWORD` with the Wi-Fi used at the UNO's location.
3. Confirm that `secrets.h` is not staged by Git. The credentials are written to the board’s local EEPROM during the first successful setup.
4. Open `friend_bot.ino` in Arduino IDE.
5. Select **Arduino UNO R4 WiFi** and the UNO's USB port.
6. Verify and upload.
7. Open Serial Monitor at `115200` baud.

Expected messages include:

```text
friend-bot starting | device=UNO-R4 | version=0.2.0-bootstrap
OTA bootstrap: connecting to <your network>
OTA bootstrap: Wi-Fi connected, IP=<device IP>
OTA bootstrap: remote download will be enabled in the next step
```

The LED should continue toggling every second. Do not move the board to a remote location until the later update-download test succeeds.

After the first successful connection, future builds can omit `secrets.h`; the board will reuse its locally stored credentials. Do not erase EEPROM unless you intentionally want to provision new credentials.

The permanent OTA artifact is published by GitHub Actions at `https://mrunalswaroop.github.io/DB_PetBot/ota/UNO-R4.bin`, and the current version is advertised by `https://mrunalswaroop.github.io/DB_PetBot/ota/manifest.json`. Copy `ota_target.example.h` to the ignored `ota_target.h`, then upload the manifest-enabled bootstrap once over USB. Do not commit `ota_target.h`. After that, future firmware commits can publish a newer version automatically; the UNO checks the manifest at startup and downloads only when the manifest version is newer than its running version.

## XIAO ESP32-S3

The XIAO uses the Arduino ESP32 OTA mechanism and a raw application `.bin`; it does not use the UNO `.ota` container. Select `Seeed XIAO ESP32S3`, 8 MB flash, and `Default with SPIFFS` so the board has `ota_0` and `ota_1` application slots. Do not select `Maximum APP (No OTA/No FS)`.

Copy `ota_target.xiao.example.h` to the ignored `ota_target.h`, add `secrets.h` with the Wi-Fi credentials for the XIAO’s current location, and upload `friend_bot.ino` once over USB. The XIAO then checks `xiao-esp32s3-manifest.json` and downloads `XIAO-ESP32S3.bin` only when the published semantic version is newer. The onboard LED is the only circuit needed for this first step; the camera module remains unused until its feature module is added.
