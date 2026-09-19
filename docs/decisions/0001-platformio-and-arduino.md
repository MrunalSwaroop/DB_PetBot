# ADR 0001: PlatformIO with Arduino Framework

## Decision

Use PlatformIO with the Arduino framework for the greenfield firmware project.

## Reason

The project needs reproducible local and GitHub Actions builds for an Arduino UNO R4 WiFi and XIAO ESP32-S3 variants, while keeping the application approachable for `.ino`-style development.

## Consequences

- Board environments and library versions can be pinned.
- The same source tree can build multiple device variants.
- GitHub Actions can build without a graphical IDE.
- The initial setup requires PlatformIO installation.
