#include <Arduino.h>

#include "board_config.h"
#include "features/led_status/led_status.h"

namespace {
LedStatus ledStatus;
}

void setup() {
  Serial.begin(115200);
  delay(100);

  ledStatus.begin(kBoardConfig.ledPin, kBoardConfig.ledActiveHigh,
                  BLINK_INTERVAL_MS);

  Serial.print("friend-bot firmware started | device=");
  Serial.print(kBoardConfig.deviceId);
  Serial.print(" | board=");
  Serial.print(kBoardConfig.boardName);
  Serial.print(" | blink_interval_ms=");
  Serial.println(BLINK_INTERVAL_MS);
}

void loop() {
  ledStatus.update(millis());
}
