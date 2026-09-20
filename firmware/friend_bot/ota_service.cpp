#include "ota_service.h"

#include <Arduino.h>
#include "device_config.h"

#if defined(ARDUINO_UNOR4_WIFI)
#include <WiFiS3.h>
#endif

namespace {
constexpr unsigned long kWifiRetryIntervalMs = 10000UL;
}

void OtaService::begin() {
#if defined(ARDUINO_UNOR4_WIFI)
  Serial.println("OTA bootstrap: starting Wi-Fi service");

  if (WIFI_SSID[0] == '\0') {
    Serial.println("OTA bootstrap: WIFI_SSID is empty; create secrets.h locally");
    return;
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("OTA bootstrap: Wi-Fi module not detected");
    return;
  }

  lastWifiRetryMs_ = 0;
  update();
#else
  Serial.println("OTA bootstrap: Wi-Fi service not enabled for this board yet");
#endif
}

void OtaService::update() {
#if defined(ARDUINO_UNOR4_WIFI)
  if (WIFI_SSID[0] == '\0' || wifiConnected_) {
    return;
  }

  const unsigned long nowMs = millis();
  if (wifiAttempted_ && nowMs - lastWifiRetryMs_ < kWifiRetryIntervalMs) {
    return;
  }

  wifiAttempted_ = true;
  lastWifiRetryMs_ = nowMs;

  Serial.print("OTA bootstrap: connecting to ");
  Serial.println(WIFI_SSID);

  if (WiFi.begin(WIFI_SSID, WIFI_PASSWORD) == WL_CONNECTED) {
    Serial.println("OTA bootstrap: Wi-Fi link connected; waiting for DHCP");

    const unsigned long dhcpStartMs = millis();
    while (millis() - dhcpStartMs < 15000UL) {
      const IPAddress ip = WiFi.localIP();
      if (ip[0] != 0 || ip[1] != 0 || ip[2] != 0 || ip[3] != 0) {
        wifiConnected_ = true;
        Serial.print("OTA bootstrap: Wi-Fi connected, IP=");
        Serial.println(ip);
        Serial.println("OTA bootstrap: remote download will be enabled in the next step");
        return;
      }
      delay(250);
    }

    Serial.println("OTA bootstrap: DHCP did not assign an IP address yet");
  } else {
    Serial.println("OTA bootstrap: Wi-Fi connection attempt did not complete");
  }
#else
  // Other board backends will be added after the UNO bootstrap is verified.
#endif
}
