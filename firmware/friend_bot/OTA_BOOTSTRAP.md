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

The permanent OTA artifact is published by GitHub Actions at `https://mrunalswaroop.github.io/DB_PetBot/ota/UNO-R4.bin`. Copy `ota_target.example.h` to the ignored `ota_target.h`, then upload the bootstrap once over USB with the current target version. Do not commit `ota_target.h`.
