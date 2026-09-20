#include "ota_service.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <cstring>
#include "device_config.h"

#if defined(ARDUINO_UNOR4_WIFI)
#include <WiFiS3.h>
#include <OTAUpdate.h>
#include "ota_usertrust_rsa_root_ca.h"
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

  const String wifiFirmwareVersion = WiFi.firmwareVersion();
  Serial.print("OTA bootstrap: Wi-Fi bridge firmware=");
  Serial.println(wifiFirmwareVersion);
  if (wifiFirmwareVersion < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.print("OTA bootstrap: upgrade bridge firmware; recommended minimum=");
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
  }

  lastWifiRetryMs_ = 0;
  update();
#else
  Serial.println("OTA bootstrap: Wi-Fi service not enabled for this board yet");
#endif
}

void OtaService::update() {
#if defined(ARDUINO_UNOR4_WIFI)
  if (ssid_[0] == '\0' || otaChecked_) {
    return;
  }

  if (wifiConnected_) {
    tryRemoteUpdate();
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

void OtaService::tryRemoteUpdate() {
#if defined(ARDUINO_UNOR4_WIFI)
  otaChecked_ = true;

  if (OTA_UPDATE_URL[0] == '\0' || OTA_TARGET_VERSION[0] == '\0') {
    Serial.println("OTA bootstrap: no update package configured");
    return;
  }

  if (strcmp(APP_VERSION, OTA_TARGET_VERSION) == 0) {
    Serial.print("OTA bootstrap: already running target version ");
    Serial.println(OTA_TARGET_VERSION);
    return;
  }

  Serial.print("OTA bootstrap: downloading version ");
  Serial.println(OTA_TARGET_VERSION);

  OTAUpdate ota;
  int ret = ota.begin("/update.bin");
  if (ret != OTAUpdate::OTA_ERROR_NONE) {
    Serial.print("OTA bootstrap: ota.begin failed: ");
    Serial.println(ret);
    return;
  }

  ret = ota.setCACert(usertrust_rsa_root_ca);
  if (ret != OTAUpdate::OTA_ERROR_NONE) {
    Serial.print("OTA bootstrap: certificate setup failed: ");
    Serial.println(ret);
    return;
  }

  const int otaSize = ota.download(OTA_UPDATE_URL, "/update.bin");
  if (otaSize <= 0) {
    Serial.print("OTA bootstrap: download failed: ");
    Serial.println(otaSize);
    return;
  }

  Serial.print("OTA bootstrap: package downloaded=");
  Serial.println(otaSize);

  ret = ota.verify();
  if (ret != OTAUpdate::OTA_ERROR_NONE) {
    Serial.print("OTA bootstrap: package verification failed: ");
    Serial.println(ret);
    return;
  }

  ret = ota.update("/update.bin");
  if (ret != OTAUpdate::OTA_ERROR_NONE) {
    Serial.print("OTA bootstrap: update failed: ");
    Serial.println(ret);
    return;
  }

  Serial.println("OTA bootstrap: update accepted; board may reboot now");
#endif
}
