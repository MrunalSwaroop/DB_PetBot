#pragma once

class OtaService {
 public:
  void begin();
  void update();

 private:
  bool wifiAttempted_ = false;
  bool wifiConnected_ = false;
  unsigned long lastWifiRetryMs_ = 0;
};
