#!/usr/bin/env python3
"""Create an Arduino UNO R4 WiFi .ota package.

The package header format follows Arduino's official ArduinoIoTCloud
bin2ota.py utility for the UNOR4WIFI target.
"""

import argparse
from pathlib import Path
import zlib

MAGIC_UNOR4WIFI = bytes.fromhex("02 10 41 23")
VERSION_COMPRESSED = bytes.fromhex("00 00 00 00 00 00 00 40")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("input_lzss", type=Path)
    parser.add_argument("output_ota", type=Path)
    args = parser.parse_args()

    compressed_payload = args.input_lzss.read_bytes()
    payload = MAGIC_UNOR4WIFI + VERSION_COMPRESSED + compressed_payload
    crc = zlib.crc32(payload) & 0xFFFFFFFF
    package = len(payload).to_bytes(4, "little") + crc.to_bytes(4, "little") + payload
    args.output_ota.write_bytes(package)


if __name__ == "__main__":
    main()
