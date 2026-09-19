#pragma once

#include <Arduino.h>

#define BOARD_NAME "seeed-xiao-esp32s3-camera"

#ifndef LED_BUILTIN
#define LED_BUILTIN 21
#endif

// The XIAO ESP32-S3 user LED is active-low on the standard board.
#define LED_PIN LED_BUILTIN
#define LED_ACTIVE_HIGH false
