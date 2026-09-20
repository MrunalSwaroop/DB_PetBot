#pragma once

class OtaService {
 public:
  void begin();
  void update();

 private:
  void tryRemoteUpdate();

  char ssid_[33] = {};
  char password_[65] = {};
  bool wifiAttempted_ = false;
  bool wifiConnected_ = false;
  bool otaChecked_ = false;
  unsigned long lastWifiRetryMs_ = 0;
};
