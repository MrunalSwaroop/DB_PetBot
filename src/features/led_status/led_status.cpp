#include "led_status.h"

void LedStatus::begin(uint8_t pin, bool activeHigh, unsigned long intervalMs) {
  pin_ = pin;
  activeHigh_ = activeHigh;
  intervalMs_ = intervalMs;
  state_ = false;
  lastChangeMs_ = millis();

  pinMode(pin_, OUTPUT);
  writeState(state_);
}

void LedStatus::update(unsigned long nowMs) {
  if (nowMs - lastChangeMs_ < intervalMs_) {
    return;
  }

  lastChangeMs_ = nowMs;
  state_ = !state_;
  writeState(state_);
}

void LedStatus::writeState(bool on) {
  const bool outputHigh = activeHigh_ ? on : !on;
  digitalWrite(pin_, outputHigh ? HIGH : LOW);
}
