#pragma once

// Device identity is compiled into the firmware and is not a secret.
#ifndef DEVICE_ID
#define DEVICE_ID "UNO-R4"
#endif

#ifndef APP_VERSION
#define APP_VERSION "0.2.0-bootstrap"
#endif

// These defaults keep the repository buildable without credentials.
// For a physical board, create secrets.h beside this file and define them there.
#ifndef WIFI_SSID
#define WIFI_SSID ""
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD ""
#endif

// Leave empty during the Wi-Fi bootstrap step. A later step will add a
// device-specific HTTPS manifest URL and the signed firmware update flow.
#ifndef OTA_MANIFEST_URL
#define OTA_MANIFEST_URL ""
#endif
