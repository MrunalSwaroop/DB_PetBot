# Change 0009: XIAO ten-second blink cycle

## Summary

Change the XIAO ESP32-S3 onboard LED timing to a ten-second complete cycle. The LED remains HIGH for 5 seconds and LOW for 5 seconds. The UNO R4 timing remains one second HIGH and one second LOW.

## OTA release

The change is included in the next GitHub Actions XIAO raw-binary artifact and XIAO-specific manifest. The XIAO must successfully complete its pending HTTPS binary transfer before this release can run remotely.

## Verification

Compile both board targets, publish the XIAO artifact, and verify after installation that the XIAO LED changes state every 5 seconds while the serial log reports the new firmware version.
