# Feature Inventory

| Feature | Version | Status | UNO-R4 | XIAO-1 | XIAO-2 | NODEMCU-1 | ESP8266-1 | Notes |
|---|---:|---|---|---|---|---|---|---|
| `led_baseline` | 0.1.0 | Active | Yes | Yes | Yes | Yes | Yes | Original one-second Arduino blink sketch |
| `wifi_provisioning` | — | Planned | Planned | Planned | Planned | Planned | Planned | Per-device credentials, never committed |
| `ota_service` | 0.3.0 | Manifest active | Active | Active | Active | Planned | Planned | UNO uses official `.ota`; XIAO uses ESP32 dual-slot raw `.bin` |
| `camera` | — | Planned | No | Planned | Planned | No | No | XIAO camera targets only |

Feature details and change history are tracked under `docs/changes/` and `CHANGELOG.md`.
