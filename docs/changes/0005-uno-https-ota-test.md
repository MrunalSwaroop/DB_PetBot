# Change 0005: UNO HTTPS OTA test

## Summary

Add the first real pull-based firmware update operation for the UNO R4 WiFi using Arduino's official `OTAUpdate` library and `.ota` package format.

## Behavior

The UNO connects to Wi-Fi, verifies the configured server CA bundle, downloads a configured `.ota` package, verifies the package, and applies it through the Wi-Fi module. The one-second LED application remains in the updated firmware.

The first test uses a temporary direct URL and target version. The general per-device manifest and GitHub target-selection workflow will be added after this one-time update succeeds.

## Security

The OTA code uses HTTPS certificate verification. The current trust bundle includes Arduino's official roots and the current Sectigo E46 root used by GitHub's certificate chain. Firmware signing and anti-rollback are later hardening steps.

## Verification

Build a `.ota` artifact with the official UNO R4 package header, publish it to the test release, upload the test bootstrap with the direct URL, and confirm the UNO downloads, verifies, reboots, and runs version `0.3.0-test`.
