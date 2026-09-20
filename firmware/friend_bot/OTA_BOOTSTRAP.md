# OTA bootstrap: current step

This step does not download firmware yet. It adds the permanent service structure and verifies that the UNO R4 WiFi can connect to its local Wi-Fi without changing the one-second LED behavior.

## Local setup

1. Copy `secrets.example.h` to `secrets.h` in this same folder.
2. Replace `WIFI_SSID` and `WIFI_PASSWORD` with the Wi-Fi used at the UNO's location.
3. Confirm that `secrets.h` is not staged by Git.
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
