# Change 0008: XIAO five-second blink cycle

## Summary

Change the XIAO ESP32-S3 onboard LED timing to a five-second complete cycle. The LED remains HIGH for 2.5 seconds and LOW for 2.5 seconds. The UNO R4 timing remains one second HIGH and one second LOW.

## OTA release

The change is included in the next GitHub Actions XIAO raw-binary artifact and XIAO-specific manifest. The board must complete the pending XIAO HTTPS transfer before this release can run remotely; the previously observed stream timeout prevented the 0.4.8 artifact from being installed.

## Verification

Compile both the UNO R4 and XIAO ESP32-S3 targets, publish the XIAO artifact, and verify after installation that the XIAO LED changes state every 2.5 seconds while the serial log continues to report the active firmware version.
