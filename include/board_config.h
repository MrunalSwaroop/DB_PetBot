#pragma once

#if defined(BOARD_UNO_R4_WIFI)
#include "../variants/uno_r4_wifi.h"
#elif defined(BOARD_XIAO_ESP32S3)
#include "../variants/xiao_esp32s3_cam.h"
#else
#error "Select a board with BOARD_UNO_R4_WIFI or BOARD_XIAO_ESP32S3"
#endif

#if defined(DEVICE_UNO_R4)
#define DEVICE_ID "UNO-R4"
#elif defined(DEVICE_XIAO_1)
#define DEVICE_ID "XIAO-1"
#elif defined(DEVICE_XIAO_2)
#define DEVICE_ID "XIAO-2"
#else
#define DEVICE_ID "UNASSIGNED"
#endif

#ifndef BLINK_INTERVAL_MS
#define BLINK_INTERVAL_MS 5000UL
#endif

struct BoardConfig {
  const char* deviceId;
  const char* boardName;
  uint8_t ledPin;
  bool ledActiveHigh;
};

static const BoardConfig kBoardConfig{
    DEVICE_ID,
    BOARD_NAME,
    LED_PIN,
    LED_ACTIVE_HIGH,
};
