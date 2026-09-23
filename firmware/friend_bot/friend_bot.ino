/*
  Friend Bot Arduino IDE firmware

  Current step: one-second onboard LED blink plus the first Wi-Fi/OTA
  bootstrap service. Actual remote firmware download is enabled only after
  Wi-Fi connectivity is verified on the UNO R4.
*/

#if __has_include("secrets.h")
#include "secrets.h"
#endif

#include "device_config.h"
#include "ota_service.h"

OtaService otaService;
unsigned long lastBlinkMs = 0;
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.print("friend-bot starting | device=");
  Serial.print(DEVICE_ID);
  Serial.print(" | version=");
  Serial.println(APP_VERSION);

  otaService.begin();
}

void loop() {
  const unsigned long nowMs = millis();

  if (nowMs - lastBlinkMs >= BLINK_INTERVAL_MS) {
    lastBlinkMs = nowMs;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
  }

  otaService.update();
}
