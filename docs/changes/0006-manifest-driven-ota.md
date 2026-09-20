# Change 0006: Manifest-driven automatic UNO OTA

## Summary

Add a startup HTTPS manifest check to the UNO R4 WiFi firmware and publish the manifest through the existing GitHub Actions and GitHub Pages pipeline. The device compares the published semantic version with its running firmware and downloads the OTA package only when the published version is newer.

## Behavior

The UNO connects using its stored Wi-Fi credentials, opens an HTTPS connection to the GitHub Pages manifest, extracts the advertised version, and performs the existing Arduino `OTAUpdate` download, verification, and update sequence only for a newer semantic version. The LED application remains active while the device is online and no update is required.

## CI/CD

Each qualifying commit runs the Arduino CLI build, the official Arduino LZSS compressor, the UNO R4 package generator, and the GitHub Pages deployment. The workflow publishes `manifest.json`, `UNO-R4.version`, and `UNO-R4.bin` under the stable Pages path.

## Verification

Compile the manifest-enabled firmware, validate the published JSON and binary headers, upload the bootstrap once over USB, and verify that the UNO reports its current version without downloading when the manifest is not newer. A later firmware commit must produce a higher manifest version and cause the device to download, verify, reboot, and report that new version.

## Security note

Manifest and firmware downloads use HTTPS certificate verification. Firmware signing, device authorization, staged rollout, and anti-rollback enforcement remain future hardening work before unattended updates are used for production devices.
