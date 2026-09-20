#!/usr/bin/env python3
"""Create an Arduino UNO R4 WiFi .ota package.

The package header format follows Arduino's official ArduinoIoTCloud
bin2ota.py utility for the UNOR4WIFI target.
"""

import argparse
from pathlib import Path

import crccheck.crc

MAGIC_UNOR4WIFI = bytes.fromhex("02 10 41 23")
VERSION_COMPRESSED = bytes.fromhex("00 00 00 00 00 00 00 40")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("input_bin", type=Path)
    parser.add_argument("output_ota", type=Path)
    args = parser.parse_args()

    payload = MAGIC_UNOR4WIFI + VERSION_COMPRESSED + args.input_bin.read_bytes()
    crc = crccheck.crc.Crc32.calc(payload)
    package = len(payload).to_bytes(4, "little") + crc.to_bytes(4, "little") + payload
    args.output_ota.write_bytes(package)


if __name__ == "__main__":
    main()
