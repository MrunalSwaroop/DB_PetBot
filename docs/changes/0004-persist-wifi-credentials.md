# Change 0004: Persist Wi-Fi credentials on the UNO

## Summary

Store the UNO R4 WiFi credentials in local EEPROM after the first USB bootstrap so future firmware updates do not need the Wi-Fi password embedded in the source tree or firmware build.

## Behavior

During the first USB setup, `secrets.h` supplies the credentials and the firmware stores them locally. Later firmware boots reuse the stored credentials even when `secrets.h` is absent from the computer used to build the firmware.

## Security

The credentials are not committed to GitHub and are not printed in the serial log. The EEPROM data is local to the board. This is a bootstrap convenience; production hardening will later evaluate encrypted storage and device-specific authentication.

## Verification

Upload with local `secrets.h`, confirm connection, remove `secrets.h` from the local sketch folder without committing it, upload a later build, and confirm the UNO reconnects using its stored credentials.
