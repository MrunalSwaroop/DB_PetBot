#include "ota_service.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <cstring>
#include "device_config.h"

#if defined(ARDUINO_UNOR4_WIFI)
#include <WiFiS3.h>
#endif

namespace {
constexpr unsigned long kWifiRetryIntervalMs = 10000UL;
constexpr uint32_t kCredentialsMagic = 0x46504254UL;

struct StoredCredentials {
  uint32_t magic;
  char ssid[33];
  char password[65];
};

bool validCredentials(const StoredCredentials& stored) {
  return stored.magic == kCredentialsMagic && stored.ssid[0] != '\0';
}
}

void OtaService::begin() {
#if defined(ARDUINO_UNOR4_WIFI)
  Serial.println("OTA bootstrap: starting Wi-Fi service");

  StoredCredentials stored{};
  EEPROM.get(0, stored);

  if (validCredentials(stored)) {
    strncpy(ssid_, stored.ssid, sizeof(ssid_) - 1);
    strncpy(password_, stored.password, sizeof(password_) - 1);
    Serial.println("OTA bootstrap: using Wi-Fi credentials stored on board");
  } else if (WIFI_SSID[0] != '\0') {
    stored.magic = kCredentialsMagic;
    strncpy(stored.ssid, WIFI_SSID, sizeof(stored.ssid) - 1);
    strncpy(stored.password, WIFI_PASSWORD, sizeof(stored.password) - 1);
    EEPROM.put(0, stored);
    strncpy(ssid_, stored.ssid, sizeof(ssid_) - 1);
    strncpy(password_, stored.password, sizeof(password_) - 1);
    Serial.println("OTA bootstrap: stored Wi-Fi credentials on board");
  } else {
    Serial.println("OTA bootstrap: no Wi-Fi credentials stored; create secrets.h for first USB setup");
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
  if (ssid_[0] == '\0' || wifiConnected_) {
    return;
  }

  const unsigned long nowMs = millis();
  if (wifiAttempted_ && nowMs - lastWifiRetryMs_ < kWifiRetryIntervalMs) {
    return;
  }

  wifiAttempted_ = true;
  lastWifiRetryMs_ = nowMs;

  Serial.print("OTA bootstrap: connecting to ");
  Serial.println(ssid_);

  if (WiFi.begin(ssid_, password_) == WL_CONNECTED) {
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
