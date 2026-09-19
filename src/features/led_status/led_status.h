#pragma once

#include <Arduino.h>

class LedStatus {
 public:
  void begin(uint8_t pin, bool activeHigh, unsigned long intervalMs);
  void update(unsigned long nowMs);

 private:
  void writeState(bool on);

  uint8_t pin_ = LED_BUILTIN;
  bool activeHigh_ = true;
  bool state_ = false;
  unsigned long intervalMs_ = 5000UL;
  unsigned long lastChangeMs_ = 0UL;
};
